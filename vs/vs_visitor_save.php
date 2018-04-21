<?php
  session_start();
  $vid=$_POST['vid'];
  $fieldname=$_POST['f'];
  $value=$_POST['v'];
	$language=$_SESSION['language'];
	include('../classes/class_visitors.php');
  $visitors=new seso_visitors();
	$test=0;
  $values=array();
	
	$values+=array($fieldname=>$value);
  $visitors->savevisitor($vid,$values);
?>