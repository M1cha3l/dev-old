<html>
<head>
<title>
insert-order.php
</title>
</head>

<body>

<?php

$idNo = $_POST["idNo"];
$supName = $_POST["supName"];
$pIdNo = $_POST["pIdNo"];
$quantity = $_POST["quantity"];
$cost = $_POST["cost"];

require("/home/grad/m_hughes/CSCI3461/lab1/Labs/hughessf");
$table = "order";

$link = mysql_connect($host, $user, $pass);
if (!$link) die("Couldn't connect to MySQL");
print "Successfully connected to server<p>";

mysql_select_db($db)
        or die("Couldn't open $db: ".mysql_error());
print "Successfully selected database \"$db\"<p>";

$query = "insert into $table values";
$query = $query."(\"$idNo\", \"$supName\", \"$pIdNo\",\"$quantity\",\"$cost\")";

print "$query<p>";

$ok = mysql_query($query);
if (!$ok) print "SQL error: ".mysql_error();

mysql_close($link);

print "<p><p>Connection closed."
?>

<p>
<a href="main1.php"> back to menu </a>

</body>

</html>