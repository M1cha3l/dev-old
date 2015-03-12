<html>
<head>
<title>
insert-supplier.php
</title>
</head>

<body>

<?php

$name = trim($_POST["name"]);
$addr = trim($_POST["addr"]);
$pnums = preg_split("/[\s,]+/", $_POST["phoneNums"]);

require("/home/grad/j_pew/3461/.3461db.php");
$table = "supplier";

$link = mysql_connect($host, $user, $pass);
if (!$link) die("Couldn't connect to MySQL");
print "Successfully connected to server<p>";

mysql_select_db($db)
        or die("Couldn't open $db: ".mysql_error());
print "Successfully selected database \"$db\"<p>";

$query = "INSERT INTO $table VALUES";
$query = $query."(\"$name\", \"$addr\")";

print "$query<p>";

$ok = mysql_query($query);
if (!$ok) {
    $pos = strpos(mysql_error(), "Duplicate");
    if ($pos === false) die("SQL error: ".mysql_error());
    else die("This supplier already exists in our records.");
}

$table = "supplierPhone";

$query = "";
foreach ($pnums as $pnum) {
    $pnum = trim($pnum);
    if (strlen($pnum)) {
        $i++;
        $query .= "(\"$pnum\", \"$name\"), ";
    }
}
if ($i) {
    $query = "INSERT INTO $table VALUES " . substr($query, 0, -2);
    print "$query<p>";
    $ok = mysql_query($query);
    if (!$ok) print "SQL error: ".mysql_error();
}

mysql_close($link);

print "<p><p>Connection closed."
?>

<p>
<a href="main1.php"> back to menu </a>

</body>

</html>
