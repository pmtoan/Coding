from flask import Flask, render_template, request, session, redirect
import os

app = Flask(__name__)

# Normal web
@app.route("/")
def hello():
	return render_template("hello.html", name="")
@app.route("/<path:path>")
def sendfile(path):
	if os.path.isfile(path) == True:
		return send_file(path)
	return render_template("404.html")

# Session example
'''
@app.route("/")
def hello():
	if "session_key" in session:
		return redirect("/home")
	return render_template("index.html", status="")
@app.route("/login", methods=["POST"])
def login():
	session["session_key"] = request.form.get('usr')
	return render_template("hello.html", name=request.form.get('usr'))
@app.route("/logout")
def logout():
	session.pop("session_key", None)
	return redirect("/")
'''

if __name__ == '__main__':
	app.secret_key = 'A0Zr98j/3yX R~XHH!jmN]LWX/,?RT'
	app.run(debug = True, host="0.0.0.0", port=80)