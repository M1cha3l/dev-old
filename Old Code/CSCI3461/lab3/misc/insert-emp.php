<html>
<head>
<title>
insert-emp.php
</title>
</head>

<body>

<?php

$esin = $_POST["esin"];
$ename = $_POST["ename"];
$ebdate = $_POST["ebdate"];
$esalary = $_POST["esalary"];
$edno = $_POST["edno"];
$esuper = $_POST["esuper"];


require("/home/grad/m_hughes/CSCI3461/lab1/Labs/hughessf");
$table = "emp";

$link = mysql_connect($host, $user, $pass);
if (!$link) die("Couldn't connect to MySQL");
print "Successfully connected to server<p>";

mysql_select_db($db)
        or die("Couldn't open $db: ".mysql_error());
print "Successfully selected database \"$db\"<p>";

$query = "insert into $table values";
$query = $query."(\"$esin\", \"$ename\", \"$ebdate\", \"$esalary\",";
if (strlen($esuper)==0) $query = $query." $edno, null)";
else $query = $query." $edno, \"$esuper\")";


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