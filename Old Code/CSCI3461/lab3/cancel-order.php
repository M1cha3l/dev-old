<html>
<head>
<title>
cancel-order.php
</title>
</head>

<body>

<?php

$oIdNo = $_POST["orderID"];

require("/home/grad/j_pew/3461/.3461db.php");
$table = "orders";

$link = mysql_connect($host, $user, $pass);
if (!$link) die("Couldn't connect to MySQL");
print "Successfully connected to server<p>";

mysql_select_db($db)
        or die("Couldn't open $db: ".mysql_error());
print "Successfully selected database \"$db\"<p>";

if (!preg_match("/^\d+$/",$oIdNo)) die("The order ID must be specified.");

$result = mysql_query("SELECT datePlaced FROM $table WHERE idNo = \"$oIdNo\"");
if (!$result) die("SQL error: ".mysql_error());
$num_rows = mysql_num_rows($result);
if (!$num_rows) die("No orders match that ID.");

list($date) = mysql_fetch_row($result);
if (strtotime($date) < strtotime("today")-(3*60*60*24))
    die("This order was placed more than three days ago. Sorry.");

$ok = mysql_query("DELETE FROM $table WHERE idNo = \"$oIdNo\"");
if (!$ok) print "SQL error: ".mysql_error();

mysql_close($link);

print "<p><p>Connection closed."
?>

<p>
<a href="main1.php"> back to menu </a>

</body>

</html>
