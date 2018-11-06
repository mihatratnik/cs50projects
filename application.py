import os
import hashlib

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Retrieve SQL data from users database
    users = db.execute("SELECT * FROM users WHERE id=:id", id=session["user_id"])
    cash = usd(users[0]["cash"])

    # Retrieve data from portfolio database
    portfolio = db.execute("SELECT * FROM portfolio WHERE username=:username ORDER BY stock_symbol", username=users[0]["username"])

    # Calculate subtotal
    subtotal = users[0]["cash"]

    # Iterate through portfolio and make the lookup
    for stock in portfolio:
        symbol = stock["stock_symbol"]
        qty = stock["stock_qty"]
        quote = lookup(symbol)
        stock["price"] = usd(float(quote["price"]))
        stock["name"] = quote["name"]
        stock["total"] = usd(float(quote["price"]) * float(qty))
        subtotal += float(quote["price"]) * float(qty)
        stock["subtotal"] = usd(subtotal)

    return render_template("/index.html", portfolio=portfolio, cash=cash, subtotal=usd(subtotal))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock symbol is submitted
        if not request.form.get("symbol"):
            return apology("Stock symbol required", 403)

        # Ensure quantity is submitted
        elif not request.form.get("shares"):
            return apology("Stock quantity required", 403)

        else:

            # Lookup name, price and symbol of input stock
            if not lookup(request.form.get("symbol")):
                return apology("Stock symbol not correct")
            else:
                quote = lookup(request.form.get("symbol"))

            # Get number of stocks and ensure it is not fractional, negative, and non-numeric
            buy_qty = request.form.get("shares")

            if buy_qty.isnumeric() == False:
                return apology("Shares input not correct", 400)

            # Get a row from users database
            select_user = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])

            # Check wheter user has enough funds to buy the stock
            if quote["price"] * float(buy_qty) > float(select_user[0]["cash"]):
                return apology("Funds not available")

            else:

                price = usd(quote["price"])
                share_value = usd(float(quote["price"])*float(buy_qty))

                # Insert information into trans table
                db.execute("INSERT INTO trans (username, stock_symbol, stock_qty, stock_value, share_value) VALUES (:username, :symbol, :stock_qty, :price, :share_value)",
                           username=select_user[0]["username"], symbol=quote["symbol"], stock_qty=buy_qty, price=price, share_value=share_value)

                # Update user funds
                db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=float(
                    select_user[0]["cash"])-(quote["price"] * float(buy_qty)), id=session["user_id"])

                # Update user portfolio
                if not db.execute("SELECT * FROM portfolio WHERE username=:username AND stock_symbol=:symbol", username=select_user[0]["username"], symbol=quote["symbol"]):

                    db.execute("INSERT INTO portfolio (username, stock_symbol, stock_qty) VALUES (:username, :symbol, :stock_qty)",
                               username=select_user[0]["username"], symbol=quote["symbol"], stock_qty=buy_qty)

                else:
                    stock_qty = db.execute("SELECT * FROM portfolio WHERE username=:username AND stock_symbol=:symbol",
                                           username=select_user[0]["username"], symbol=quote["symbol"])

                    db.execute("UPDATE portfolio SET stock_qty=:stock_qty WHERE username=:username AND stock_symbol=:symbol", stock_qty=float(
                        stock_qty[0]["stock_qty"]) + float(buy_qty), username=select_user[0]["username"], symbol=quote["symbol"])

                # Redirect user to home page
                return redirect("/")

    else:

        return render_template("/buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    finance_users = db.execute("SELECT * FROM users WHERE id=:id", id=session["user_id"])
    username = finance_users[0]["username"]
    finance_trans = db.execute("SELECT * FROM trans WHERE username=:username", username=username)

    for stock in finance_trans:
        stock_symbol = stock["stock_symbol"]
        stock_qty = stock["stock_qty"]
        stock_value = stock["stock_value"]
        trans_time = stock["trans_time"]

    return render_template("/history.html", finance_trans=finance_trans)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not hashlib.sha256(request.form.get("password").encode('utf-8')).hexdigest():
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure that the stock symbol is input
        if not request.form.get("symbol"):
            return apology("Symbol required", 400)

        else:

            # lookup the stock name, symbol and value via API
            quote = lookup(request.form.get("symbol"))

            # Ensure that stock symbol is correct
            if quote is None:
                return apology("Symbol not correct", 400)

            # If symbol correct return template
            else:

                name = quote["name"]
                price = usd(float(quote["price"]))
                symbol = quote["symbol"]

                return render_template("/price.html", name=name, price=price, symbol=symbol)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("/quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Make sure, username is submitted
        if not request.form.get("username"):
            return apology("Username required", 400)

        # Make sure, password is submitted
        if not request.form.get("password"):
            return apology("Password required", 400)

        # Make sure, password confirmation is submitted
        if not request.form.get("confirmation"):
            return apology("You must confirm password", 400)

        # Check whether password and confirmation match
        if not request.form.get("password") == request.form.get("confirmation"):
            return apology("Passowrd and confirmation do not match")

        # Hash inserted password
        hash = hashlib.sha256(request.form.get("password").encode('utf-8')).hexdigest()

        # Insert new user into the database db
        reg_user = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                              username=request.form.get("username"), hash=hash)

        # Make sure, user is registered
        if not reg_user:
            return apology("Username already taken", 400)

        # Query database for username
        check_user = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Create a session
        session["user_id"] = check_user[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Get session ID
    users = db.execute("SELECT * FROM users WHERE id=:id", id=session["user_id"])

    # Get list of available stock
    portfolio = db.execute("SELECT * FROM portfolio WHERE username=:username", username=users[0]["username"])

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Make sure symbol is submitted
        if not request.form.get("symbol"):
            return apology("Choose a stock", 400)

        # Make sure number of stocks are submited
        elif not request.form.get("shares"):
            return apology("Choose no. of stocks", 400)

        else:

            sell_qty = int(request.form.get("shares"))

            # Lookup values for stock
            quote = lookup(request.form.get("symbol"))
            symbol = quote["symbol"]
            price = quote["price"]
            name = quote["name"]

            # Update cash in users
            cash = users[0]["cash"] + float(quote["price"]) * float(request.form.get("shares"))
            db.execute("UPDATE users SET cash=:cash WHERE id=:id", cash=cash, id=session["user_id"])

            # Update portfolio
            username = users[0]["username"]
            stock_qty = db.execute(
                "SELECT stock_qty FROM portfolio WHERE username=:username AND stock_symbol=:symbol", username=username, symbol=symbol)

            qty = 0
            for stock in stock_qty:
                qty = stock["stock_qty"]

            stock_qty = qty - sell_qty

            if stock_qty < 0:
                return apology("You do not have enough shares", 400)

            db.execute("UPDATE portfolio SET stock_qty=:stock_qty WHERE username=:username AND stock_symbol=:symbol",
                       stock_qty=stock_qty, username=username, symbol=symbol)

            # Insert transactions
            stock_qty = int(request.form.get("shares")) * -1
            share_value = usd(price * float(stock_qty))
            db.execute("INSERT INTO trans (username, stock_symbol, stock_qty, stock_value, share_value) VALUES (:username, :symbol, :stock_qty, :price, :share_value)",
                       username=username, symbol=symbol, stock_qty=stock_qty, price=usd(price), share_value=share_value)

            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:

        # Get all stocks in portfolio for drop-down
        for stock in portfolio:
            symbol = stock["stock_symbol"]
            stock["symbol"] = symbol

        return render_template("/sell.html", portfolio=portfolio)


@app.route("/change_pass", methods=["GET", "POST"])
@login_required
def change_pass():
    """Change user password"""

    # User reaches link via "GET"
    if request.method == "GET":

        return render_template("/change_pass.html")

    # User reaches link via "POST"
    else:

        # Make sure all fileds are filled
        if not request.form.get("pass_old") and not request.form.get("pass_new") and not request.form.get("confirmation"):
            return apology("All fields are required", 400)

        # Hash inserted password
        hash = hashlib.sha256(request.form.get("pass_old").encode('utf-8')).hexdigest()

        # Fetch hashed old password
        finance_users = db.execute("SELECT * FROM users WHERE id=:id", id=session["user_id"])

        # Make sure old password is correct
        if not hash == finance_users[0]["hash"]:
            return apology("Old password not correct", 400)

        else:

            # Make sure new password is confirmed
            if request.form.get("pass_new") == request.form.get("confirmation"):

                # Hash new password
                hash = hashlib.sha256(request.form.get("pass_new").encode('utf-8')).hexdigest()

                # Update has in users table
                db.execute("UPDATE users SET hash=:hash WHERE id=:id", hash=hash, id=session["user_id"])

                # Redirect to index
                return redirect("/")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
