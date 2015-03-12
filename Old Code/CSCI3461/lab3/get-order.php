<html>
<head>
<title>
get-order.php
</title>
</head>

<body>
<b><font size="5">Add New Order</font></b>
<p>
<form action="insert-order.php" method="POST">
<b>Enter the order number:</b>
<input type="text" name="idNo">
<p>
<b>Enter the order supplier's name:</b>
<input type="text" name="supName">
<p>
<b>Enter the order date:</b>
<input type="text" name="date">
<p>
<b>Enter on separate lines the part number, quantity and unit price for parts in this order:</b>
<p>
<textarea rows="10" cols="20" name="parts"></textarea>
<p>
<input type="submit" value="submit">
</form>
</body>

<a href="main1.php"> back to menu </a>

</html>
