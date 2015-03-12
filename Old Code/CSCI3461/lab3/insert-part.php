<html>
<head>
<title>
insert-part.php
</title>
</head>

<body>

<?php

$idNo = trim($_POST["idNo"]);
$price = trim(str_replace("$","", $_POST["price"]));
$descr = trim($_POST["descr"]);
$stock = trim($_POST["stock"]);

require("/home/grad/j_pew/3461/.3461db.php");
$table = "part";

$link = mysql_connect($host, $user, $pass);
if (!$link) die("Couldn't connect to MySQL");
print "Successfully connected to server<p>";

mysql_select_db($db)
        or die("Couldn't open $db: ".mysql_error());
print "Successfully selected database \"$db\"<p>";

if (!preg_match("/^\d+$/",$idNo)) die("The part ID must be specified.");
if (!preg_match("/^(\d*[.]?\d+|\d+[.]?\d*)$/",$price)) die("The price must be specified.");
if (!preg_match("/^\d+$/",$stock)) die("The stock quantity must be specified.");

$query = "INSERT INTO $table VALUES";
$query = $query."(\"$idNo\", \"$price\", \"$descr\",\"$stock\")";

print "$query<p>";

$ok = mysql_query($query);
if (!$ok) {
    $pos = strpos(mysql_error(), "Duplicate");
    if ($pos === false) die("SQL error: ".mysql_error());
    else die("This part ID already exists in our records.");
}

mysql_close($link);

print "<p><p>Connection closed."
?>

<p>
<a href="main1.php"> back to menu </a>

</body>

</html>
