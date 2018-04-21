<?php
	session_start();
	$vid=$_GET['id'];
	$language=$_SESSION['language'];
	include('../inc/show.inc');
	include('../inc/show_input.inc');
	include('../classes/class_visitors.php');
	include('../classes/class_users.php');
	include('../classes/class_labels.php');
  include('../inc/datefunctions.inc');

	echo "<script>
	function save_visitor(vid,field)
	{ f=field.name;
	  v=field.value;
		$.post('vs/vs_visitor_save.php',{vid:vid,f:f,v:v});
	}
	</script>";
	
	$visitors=new seso_visitors();
	$users=new seso_users($language);
	$labels = new seso_labels("vs_visitor_edit",$language);
	$action="onchange='save_visitor(".$vid.",this);'";
  $now=actualdatecode();

	echo "<div class='container'>";
	if ($vid>0)
	{	$visitor=$visitors->getvisitor($vid,"*"); 

  	sh_grouptitle($labels->getlabel('visitor').": ".$visitor['email']);

	  echo "<div class='datablock'>";
	  
    $options=$users->members;
		$opt=array();
		for ($t1=0; $t1<5; $t1++) { $opt[$t1]=$options[$t1];}
		shi_options_id($labels->getlabel('authorized'),'authorized',$visitor['authorized'],$opt,$action);
		
		shi_inputfield($labels->getlabel('email'),'email',$visitor['email'],120,$action);
		shi_inputfield($labels->getlabel('password'),'pw',$visitor['pw'],120,$action);
		
		echo "</div>";
	} 
  else
	{ echo "<div".$labels->getlabel('novisitorselected')."</div>";}		

  echo "<br></div>";
?>