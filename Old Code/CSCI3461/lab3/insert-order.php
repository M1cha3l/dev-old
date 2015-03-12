<html>
<head>
<title>
insert-order.php
</title>
</head>

<body>

<?php

$oIdNo = trim($_POST["idNo"]);
$supName = trim($_POST["supName"]);
$date = trim($_POST["date"]);
$orderItems = array_filter(explode("\n", $_POST["parts"]), "trim");

require("/home/grad/j_pew/3461/.3461db.php");
$link = mysql_connect($host, $user, $pass);
if (!$link) die("Couldn't connect to MySQL");
print "Successfully connected to server<p>";

mysql_select_db($db)
        or die("Couldn't open $db: ".mysql_error());
print "Successfully selected database \"$db\"<p>";

if (!preg_match("/^\d+$/",$oIdNo)) die("The order ID must be specified.");
if (!strtotime($date)) die("The date entered is invalid.");
if (!count($orderItems)) die("Empty orders are not allowed.");

$query = "INSERT INTO orders VALUES ";
$query .= "(\"$oIdNo\", \"$supName\", \"$date\")";

print "$query<p>";

$ok = mysql_query($query);
if (!$ok) {
    $pos = strpos(mysql_error(), "Duplicate");
    if ($pos === false) {
        $pos = strpos(mysql_error(), "foreign key constraint");
        if ($pos !== false) die("This supplier does not exist in our records.");
        else die("SQL error: ".mysql_error());
    } else die("This order ID already exists in our records.");
}

$query = "";
foreach ($orderItems as $line) {
    list($partNo, $quantity, $unitPrice) = preg_split("/[\s,]+/", $line);
    $unitPrice = str_replace("$", "", $unitPrice);

    $query .= "(\"$partNo\", \"$oIdNo\", \"$quantity\", \"$unitPrice\"), ";
}
$query = "INSERT INTO op VALUES " . substr($query, 0, -2);

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
