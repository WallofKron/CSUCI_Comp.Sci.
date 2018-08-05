#!/usr/bin/python
import psycopg2
from flask import Flask, render_template, url_for, request, redirect
from datadog import statsd

app = Flask(__name__)

def insert_profile(name,email,password):
    con = None
    try:
        con = psycopg2.connect(dbname='d6499q33pp3bp9', user='pdyzlyewnromsl', password='0d93ce4851b32fa7388410a08d7686451adedda0f40f589d166737539667fe0d', host='ec2-107-20-195-181.compute-1.amazonaws.com', port=5432)
        cur = con.cursor()
       	cur.execute('INSERT INTO registration_table (username,email,password) VALUES(%s,%s, %s)', (name,email,password))
       	con.commit()
       	cur.close()

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)

    finally:
        if con is not None:
            con.close()

def validate_user(name,email,password):
    con = None
    try:
        con = psycopg2.connect(dbname='d6499q33pp3bp9', user='pdyzlyewnromsl', password='0d93ce4851b32fa7388410a08d7686451adedda0f40f589d166737539667fe0d', host='ec2-107-20-195-181.compute-1.amazonaws.com', port=5432)
        cur = con.cursor()
	cur.execute("SELECT username FROM registration_table WHERE username=%s and email=%s and password=%s", (name,email,password,)) 
	if cur.fetchone() is not None:
		return True
	else:
		return False

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if con is not None:
            con.close()

def check_db(name):
    con = None
    try:
        con = psycopg2.connect(dbname='d6499q33pp3bp9', user='pdyzlyewnromsl', password='0d93ce4851b32fa7388410a08d7686451adedda0f40f589d166737539667fe0d', host='ec2-107-20-195-181.compute-1.amazonaws.com', port=5432)
        cur = con.cursor()
        cur.execute("SELECT username FROM registration_table WHERE username=%s", (name,))
    	if cur.fetchone() is not None:
		return True
	else:
		return False

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if con is not None:
            con.close()


@app.route('/login',methods=['POST','GET']) 
def login_home():
	statsd.increment('web.login_page_views')
	if request.method=='POST':
		name = request.form['u']
		email = request.form['e']
		password = request.form['p']
		if validate_user(name,email,password):
			return redirect(url_for('login_pass'))
		else:
			return redirect(url_for('login_fail'))
	else:
		return render_template('login.html')

@app.route('/',methods=['POST','GET'])
def signup_home():
	statsd.increment('web.signup_page_views')
	if request.method=='POST':
		name = request.form['u']
        	email = request.form['e']
        	password = request.form['p']
	   	if check_db(name):
			return redirect(url_for('signup_fail'))
		else:
        		insert_profile(name,email,password)
			return redirect(url_for('signup_pass'))
	else:
		return render_template('signup.html')

@app.route('/login_pass')
def login_pass():
    con = None
    try:
        con = psycopg2.connect(dbname='d6499q33pp3bp9', user='pdyzlyewnromsl', password='0d93ce4851b32fa7388410a08d7686451adedda0f40f589d166737539667fe0d', host='ec2-107-20-195-181.compute-1.amazonaws.com', port=5432)
        cur = con.cursor()
        cur.execute("SELECT *FROM alumniandfriends")
	rows = cur.fetchall()

	return render_template('records.html',rows = rows)

    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if con is not None:
            con.close()

@app.route('/login_fail')
def login_fail():
	return render_template('login_fail.html')

@app.route('/signup_fail')
def signup_fail():
	return render_template('signup_fail.html')
#	return "Username is already taken."

@app.route('/signup_pass')
def signup_pass():
	return render_template('signup_pass.html')
#	return "You have successfully signed up."

@app.route('/')
def main():
	signup_home()
	
if __name__ == '__main__':
    app.run(port=5000)
