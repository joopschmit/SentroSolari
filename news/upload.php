<?php
  $nid=$_GET['id'];
	if ( 0 < $_FILES['file']['error'] ) 
	{ echo 'Error: ' . $_FILES['file']['error'] . '<br>';}
  else 
	{ move_uploaded_file($_FILES['file']['tmp_name'], 'img/' . $nid."_".$_FILES['file']['name']);
	  echo 1;
	}
?>