<html>
<head>
<title>
print-table.php
</title>
</head>
<body>

<?php

$table = $_POST["table"];

function prtable($table) {
	print "<table border=1>\n";
	while ($a_row = mysql_fetch_row($table)) {
		print "<tr>";
		foreach ($a_row as $field) print "<td>$field</td>";
		print "</tr>";
	}
	print "</table>";
}

require("/home/grad/m_hughes/CSCI3461/lab1/Labs/hughessf");

$link = mysql_connect($host, $user, $pass);
if (!$link) die("Couldn't connect to MySQL");
print "Successfully connected to server<p>";

mysql_select_db($db)
	or die("Couldn't open $db: ".mysql_error());
print "Successfully selected database \"$db\"<p>";

$result = mysql_query("select * from $table");
$num_rows = mysql_num_rows($result);
print "There are $num_rows rows in the table<p>";

prtable($result);

mysql_close($link);

print "<p><p>Connection closed. Bye..."
?>

<p>
<a href="get-table.php"> back </a>
</body>
</html>