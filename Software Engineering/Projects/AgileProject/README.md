# AP7

http://funky-rivers.herokuapp.com is the signup page.  Here is where the new user can register their username, email, and password.
If either the username or email is already registered with an existing profile, the attempt is redirected to a failure page directing 
the user to "try again".  Otherwise, if the sign-up is a success, the new user is redirected to a success page where a link forwards them
to the login page.  At the login page a user can sign in using the information they just entered into the sign-up page.  If the login
is successful, a list of employers will be shown to the user's screen; however, if the login is a failure, the user is redirected to a 
failure page where a link forwards them to attempt another login.

http://funky-rivers.herokuapp.com/signup_pass : successful signup page with link forwarding to login page.
http://funky-rivers.herokuapp.com/signup_fail : failure signup page where link forwards back to signup page.
http://funky-rivers.herokuapp.com/login : login page.
http://funky-rivers.herokuapp.com/login_fail : login failure page where link forwards user back to login page.
http://funky-rivers.herokuapp.com/login_pass : user is shown alumniandfriends list of employers.
