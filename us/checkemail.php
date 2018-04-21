<?php
  session_start();
	$sid=session_id();
	$language=$_SESSION['language'];
	$uid=$_GET['id'];
	include('../inc/show.inc');
	include('../classes/class_visitors.php');
	include('../classes/class_labels.php');
	include('../classes/class_users.php');
  require_once('../Rmail/Rmail.php');
  
	$labels = new seso_labels("checkemail",$language);
	$vs=new seso_visitors();
  $users=new seso_users($language);
	$users->saveuser($uid,array('sessionid'=>$sid));
  $user=$users->getuser($uid,'user');
  
	$mail = new Rmail();
	$mail->setFrom('Sentro Solari Check<checkmail@moval.nl>');
	$mail->setSubject($labels->getlabel('checkuseremail'));
	$mail->setPriority('high');

  $txt=$labels->getlabel('checkemailtext');
	$txt.="\n".$labels->getlabel('checkurl')."?uid=".$uid."&sid=".$sid."\n";
	$txt.="\n".$labels->getlabel('checkurltext')."\n";
	$txt.="\n".$labels->getlabel('thankyoucheck');

	$html="<div>".nl2br($labels->getlabel('checkemailhtml'));
	$html.="<br><a href='".$labels->getlabel('checkurl')."?uid=".$uid."&sid=".$sid."' target='_new'>".$labels->getlabel('clickhere')."</a><br>";
	$html.="<br>".nl2br($labels->getlabel('checkurltext'))."<br>";
	$html.="<br>".nl2br($labels->getlabel('thankyoucheck'))."</div>";

	$mail->setText($txt);
	$mail->setHTML($html);
    
  $mail->setReceipt('info@moval.nl');
  $mail->addEmbeddedImage(new fileEmbeddedImage('https://www.moval.nl/sentrosolari/img/logoSentroSolari.jpg'));
  $address = $user['user'];
  $result  = $mail->send(array($address));

	echo "<div class='container'>";
	echo "<div class='datablock'>";
	sh_grouptitle($labels->getlabel('emailcheck'));
  sh_showfield(1,$labels->getlabel('sendto'),$user['user']);
  sh_showfield(1,$labels->getlabel('subject'),$labels->getlabel('checkuseremail'));
	sh_grouptitle($labels->getlabel('checkprocedure'));
	echo "<div>".$labels->getlabel('checkproceduretext')."</div>";	
	echo "</div><br></div>";
?>