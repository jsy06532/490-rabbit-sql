<?php

class loginDB
{
	private $logindb;

	public function __construct()
	{	
		// Connect to database host
		$this->logindb = new mysqli("127.0.0.1","testuser","12345","login");

		if ($this->logindb->connect_errno != 0)
		{
			echo "Error connecting to database: ".$this->logindb->connect_error.PHP_EOL;
			exit(1);
		}
		echo "correctly connected to database".PHP_EOL;
	}

	public function validateLogin($username,$password)
	{
		$un = $this->logindb->real_escape_string($username);
		$pw = $this->logindb->real_escape_string($password);
		$statement = "select * from users where screenname = '$un'";
		$response = $this->logindb->query($statement);

		while ($row = $response->fetch_assoc())
		{
			echo "checking password for $username".PHP_EOL;
			if ($row["password"] == $pw)
			{
				echo "passwords match for $username".PHP_EOL;
				return 1;// password match
			}
			echo "passwords did not match for $username".PHP_EOL;
		}
		return 0;//no users matched username
	}
	

	public function newRegister($username,$password)
	{
		if ($this->validateLogin($username,$password))
		{
			echo "User already found in database! Registration prevented.";
			return 0; // user already exists
		}
		else
		{
			$un = $this->logindb->real_escape_string($username);
			$pw = $this->logindb->real_escape_string($password);
			
			$statement = "INSERT INTO users (screenname, password) VALUES('$username', '$password')";
			$response = $this->logindb->query($statement);
			
			return 1; // registered?
		}
	}

}
?>