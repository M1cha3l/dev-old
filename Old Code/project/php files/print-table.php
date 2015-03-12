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
	while ($a_field = mysql_fetch_field($table)) {
        print "<th>" . $a_field->name . "</th>";
    }
	while ($a_row = mysql_fetch_row($table)) {
		print "<tr>";
		foreach ($a_row as $field) {
            if (strpos($field, ".") === false) {
                print "<td>$field</td>";
            } else {
                print "<td>$" . substr($field, 0, -2) . "</td>";
            }
        }
		print "</tr>";
	}
	print "</table>";
}

require("/home/grad/j_pew/3461/.3461db.php");

$link = mysql_connect($host, $user, $pass);
if (!$link) die("Couldn't connect to MySQL");
print "Successfully connected to server<p>";

mysql_select_db($db)
	or die("Couldn't open $db: ".mysql_error());
print "Successfully selected database \"$db\"<p>";

$result = mysql_query("SELECT * FROM $table");
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
