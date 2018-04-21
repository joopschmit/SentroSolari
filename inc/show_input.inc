<?php

	function datumselect($soort,$veld,$stand,$child,$actie="")
	{ global $_SESSION;
		$taal=$_SESSION['user']['taal'];
		$ts[0]=array("Stel de datum in met "," en ","herstellen");
		$ts[1]=array("Adjust the date with "," and ","undo");
		$ts[2]=array("Ajuste la fecha con "," y ","deshacer");
	
		$datum=datumtekst($stand); 
		$knoppen1="< < < "; $knoppen2=" > > >";
		if ($soort==1) {$datum=substr($datum,3,7); $knoppen1="< < "; $knoppen2=" > >";}
		if ($soort==2) {$datum=substr($datum,6,4); $knoppen1="< "; $knoppen2=" >";}
		$popup=$ts[$taal][0].$knoppen1.$ts[$taal][1].$knoppen2; $herstellen=$ts[$taal][2];
		if ($child=="") { $child=0;}
		echo "<div style='padding:5px 0px 5px 0px;'>";
		echo "<a href=# onclick='datum_aanpassen(\"jaar\",".$soort.",\"".$veld."\",-1,\"".$child."\"); return false;'>";
		echo "<img class='datumknop' id='jaarmin' src='figuren/kleiner.gif' onmouseout='if (gewijzigd>0) {".$actie." gewijzigd=0;}'></a> \n";
		
		if ($soort<2)
		{ echo "<a href=# onclick='datum_aanpassen(\"maand\",".$soort.",\"".$veld."\",-1,\"".$child."\"); return false;'>";
		  echo "<img class='datumknop' id='maandmin' src='figuren/kleiner.gif' onmouseout='if (gewijzigd>0) {".$actie." gewijzigd=0;}'></a> \n";
		}

		if ($soort<1)
		{ echo "<a href=# onclick='datum_aanpassen(\"dag\",".$soort.",\"".$veld."\",-1,\"".$child."\"); return false;'>";
		  echo "<img class='datumknop' id='dagmin' src='figuren/kleiner.gif' onmouseout='if (gewijzigd>0) {".$actie." gewijzigd=0;}'></a> \n";
		}
		echo "<input class=\"datuminvoer\" type=\"text\" onchange='".$actie."' title=\"".$popup."\" name=\"".$veld."\" id=\"".$veld."\" value=\"".$datum."\">";
		if ($soort<1)
		{ echo "<a href=# onclick='datum_aanpassen(\"dag\",".$soort.",\"".$veld."\",1,\"".$child."\"); return false;'>";
		  echo "<img class='datumknop' id='dagplus' src='figuren/groter.gif' onmouseout='if (gewijzigd>0) {".$actie." gewijzigd=0;}'></a> \n";
		}
		if ($soort<2) 
		{ echo "<a href=# onclick='datum_aanpassen(\"maand\",".$soort.",\"".$veld."\",1,\"".$child."\"); return false;'>";
		  echo "<img class='datumknop' id='maandplus' src='figuren/groter.gif' onmouseout='if (gewijzigd>0) {".$actie." gewijzigd=0;}'></a> \n";
		} 
		
		echo "<a href=# onclick='datum_aanpassen(\"jaar\",".$soort.",\"".$veld."\",1,\"".$child."\"); return false;'>";
		echo "<img class='datumknop' id='jaarplus' src='figuren/groter.gif' onmouseout='if (gewijzigd>0) {".$actie." gewijzigd=0;}'></a> \n";
		
		echo "<a href=# onclick='$(\"#".$veld."\").val(\"".$datum."\");".$actie."' return false;'>";
		echo "<img class='datumknop' id='herstel' src='figuren/herstellen.gif' title='".$herstellen."' style='vertical-align:middle; border:0;'></a> \n";
    echo "</div>";
		echo "<div id='".$veld."_dag' style='width:240px; text-align:center;'>".dagnaam($stand)."</div>";
	}

	function tijdselect($veld,$stand,$child,$actie="")
	{ global $_SESSION;
		$taal=$_SESSION['user']['taal'];
		$ts[0]=array("Stel de tijd in met < < en > >","herstellen");
		$ts[1]=array("Adjust the time with < < and > >","undo");
		$ts[2]=array("Ajustar el tiempo con < < y > >","deshacer");
		if ($child!=0) { $child="document.".$formnaam.".".$child;}
		$tijd=tijdtekst($stand);
		$popup=$ts[$taal][0]; $herstellen=$ts[$taal][1];
		echo "<div style='padding:5px 0px 5px 25px;'>";
		echo "<a href=# onclick='tijd_aanpassen(\"uren\",\"".$veld."\",-1,\"".$child."\"); return false;'>";
		echo "<img class='datumknop' src='figuren/kleiner.gif' onmouseout='if (gewijzigd>0) {".$actie." gewijzigd=0;}'></a> \n";
		echo "<a href=# onclick='tijd_aanpassen(\"minuten\",\"".$veld."\",-1,\"".$child."\"); return false;'>";
		echo "<img class='datumknop' src='figuren/kleiner.gif' onmouseout='if (gewijzigd>0) {".$actie." gewijzigd=0;}'></a> \n";
		echo "<input class='datuminvoer' type=text title='".$popup."' onchange='".$actie."' name='".$veld."' id='".$veld."' value='".$tijd."'>";
		echo "<a href=# onclick='tijd_aanpassen(\"minuten\",\"".$veld."\",1,\"".$child."\"); return false;'>";
		echo "<img class='datumknop' src='figuren/groter.gif' onmouseout='if (gewijzigd>0) {".$actie." gewijzigd=0;}'></a> \n";
		echo "<a href=# onclick='tijd_aanpassen(\"uren\",\"".$veld."\",1,\"".$child."\"); return false;'>";
		echo "<img class='datumknop' src='figuren/groter.gif' onmouseout='if (gewijzigd>0) {".$actie." gewijzigd=0;}'></a> \n";
		echo "<a href=# onclick='$(\"#".$veld."\").val(\"".$tijd."\"); ".$actie." return false;'>";
		echo "<img class='datumknop' src='figuren/herstellen.gif' title='".$herstellen."' style='vertical-align:middle; border:0;'></a> \n";
    echo "</div>";
	}
  function shi_inputfield($label,$name,$value,$maxlength,$action="")
	{	echo "\n<div class='labels'>".$label."</div>";
		echo "\n<div class='input'>";
		echo "\n<input type=text name='".$name."' id='".$name."' maxlength=".$maxlength." value=\"".stripslashes($value)."\" ".$action.">";
		echo "\n</div><br>";
	}

	function shi_inputtext($label,$name,$value,$rows,$action="")
	{	echo "\n<div class='labels'>".$label."</div>";
		echo "\n<div class='input'>";
		echo "\n<textarea rows=".$rows." id='".$name."' name='".$name."' ".$action.">".stripslashes($value)."</textarea>";
		echo "\n</div>";
	}

  function selectiebox($naam,$waarde,$van,$tot,$actie="")
	{	$box="<select name='".$naam."' id=".$naam." class='kiezen' ".$actie.">";
		$box.="<option value=''>";
		for ($x=$van; $x<=$tot; $x++)
		{if ($waarde==$x)
			 {$box=$box."<option selected value=".strval($x).">".strval($x);}
			 else
			 {$box=$box."<option value=".strval($x).">".strval($x);}
		}
		$box=$box."</select>";
		return $box;
	}

  function shi_selectpositions($label,$naam,$waarde,$van,$tot,$actie="")
	{	echo "<div class='labels'>".$label."</div>";
		echo "<div class='input'>";
		echo "<select name='".$naam."' class='selectoptions' ".$actie.">";
		for ($x=$van; $x<=$tot; $x++)
		{if ($waarde==$x)
			 {echo "<option selected value=".strval($x).">".strval($x);}
			 else
			 {echo "<option value=".strval($x).">".strval($x);}
		}
		echo "</select>";
		echo "</div>";
	}

	function keuzelijst($label,$naam,$waarde,$reeks,$actie="")
	{	echo "<div class='gegevensblok'>";
		echo "<div class='labels'>".$label."</div>";
		echo "<div class='invoer'>";
		echo "<select name='".$naam."' id='".$naam."' ".$actie.">";
		foreach($reeks as $key=>$val)
		{ if (strtolower($waarde)==strtolower($val))
		  {echo "<option  value='".strval($val)."' selected>".$val;}
		  else
		  {echo "<option  value='".strval($val)."'>".$val;}
		}
		echo "</select>";
		echo "</div>";
		echo "</div>";
	}

	function shi_options($name,$value,$options,$action="") 
	{	echo "<select name='".$name."' id='".$name."' ".$action.">";
		foreach($options as $key=>$val)
		{ if ($value==$key) { $selected="SELECTED";} else { $selected="";}
		  echo "<option  value=".$key." ".$selected.">".$val;
		}
		echo "</select>";
	}

  function shi_options_id($label,$idname,$id,$options,$action)
	{	echo "<div class='labels'>".$label."</div>";
		echo "<div class='input'>";
		echo "<select id='".$idname."' name='".$idname."' ".$action.">";
		foreach($options as $key=>$val)
		{ if ($id==$key)
		  { echo "<option selected value=".$key.">".$val;}
		  else
		  { echo "<option value=".$key.">".$val;}
		}
		echo "</select>";
		echo "</div><br>";
	}

	function keuzebox_sql($label,$sql,$idveld,$naamveld,$naam,$actueelid,$reeks,$actie)
	{ global $q;
		$q->query($sql);
		$teller=0; 
    echo "\n<div class='gegevensblok'>";
		echo "\n<div class='labels'>".$label."</div>";
		echo "\n<div class='invoer'>";
		echo "\n<select name='".$naam."' id='".$naam."' ".$actie.">\n";
		if ($reeks!=1 && $reeks!=10)
		{ echo "\n<option value=0>&nbsp;";}
  	while ($row = $q->next_record())
		{	if ($reeks!=1)
		  { if ($row[$idveld]==$actueelid) {$selected="selected";} else {$selected="";}}
		  else
		  { if ($teller==$actueelid) {$selected="selected";} else {$selected="";}}
      if ($reeks==1) {$waarde=$teller;} else {$waarde=$row[$idveld];}
      echo "\n<option value='".$waarde."' ".$selected.">".$row[$naamveld];
      $teller++;
		}
		echo "\n</select>";
		echo "\n</div>";
		echo "\n</div>\n";
	}

	function keuzebox($label,$tabel,$selectie,$idveld,$naamveld,$naam,$actueelid,$actie)
	{ //global  $q;
    if (strpos($naamveld,",")>0)
    { $velden=explode(",",$naamveld); }
    else
    { $velden=array($naamveld);}
    $sql="select distinct ".$idveld.", ".$naamveld." from ".$tabel." where ".$velden[0]."<>''";
    if ($selectie!="") {$sql=$sql." and ".$selectie;};
    $sql=$sql." order by ".$naamveld;
		//$q->query($sql);
    echo "\n<div class='gegevensblok'>";
		if ($label!='0') {echo "\n<div class='labels'>".$label."</div>";}
		echo "\n<div class='invoer'>";
		echo "\n<select name='".$naam."' id='".$naam."' ".$actie.">";
		echo "\n<option value='0'>&nbsp;";
    if (strpos($naamveld,",")>0)
    { $velden=explode(",",$naamveld); }
    else
    { $velden=array($naamveld);}
/*
		while ($row = $q->next_record())
		{	if ($row[$idveld]==$actueelid) {$selected="selected";} else {$selected="";}
      $tekst="";
      reset($velden);
      while (list($key,$var)=each($velden))
      { $tekst.=$row[$var]." ";}
			echo "\n<option value='".$row[$idveld]."' ".$selected.">".$tekst;
		}
		echo "\n</select>";
		echo "\n</div>";
		echo "\n</div>\n";
*/
	}

	function keuzebox_users($label,$selectie,$naam,$actueelid,$actie="") //als actueelID voldoet aan selectie wordt deze toch toegevoegd.
	{ global $q,$_SESSION;
    $sql="select pid, naam_compleet from 0_users where cust_id=".$_SESSION['user']['cust_id']." and pid>0 ";
    if ($selectie!="") {$sql=$sql." and (".$selectie.")";};
    if ($actueelid>0)
    { $sql=$sql." or (cust_id=".$_SESSION['user']['cust_id']." and pid=".$actueelid.")";}
    $sql.=" order by naam_compleet";
  	$q->query($sql);
    echo "\n<div class='gegevensblok'>";
		echo "\n<div class='labels'>".$label."</div>";
		echo "\n<div class='invoer'>";
    echo "\n<select name='".$naam."' id='".$naam."' ".$actie.">";
		echo "\n<option value=0>&nbsp;";
		while ($row = $q->next_record())
		{	if ($row['pid']==$actueelid) {$selected="selected";} else {$selected="";}
			echo "\n<option value=".$row['pid']." ".$selected.">".$row['naam_compleet'];
		}
		echo "\n</select>";
		echo "\n</div>";
		echo "\n</div>\n";
	}

	function shi_textbox($label,$name,$actualvalue,$rows,$action="")
  { echo "\n<div class='datablock'>";
		echo "\n<div class='labels'>".$label."</div>";
		echo "\n<div class='invoer'>";
		echo "\n<textarea name='".$name."' id='".$name."' rows=".$rows." cols=40 ".$action.">".stripslashes($actualvalue)."</textarea>";
		echo "\n</div>";
		echo "\n</div>\n";
  }

	function invoerbox($label,$variabele,$waarde,$regels,$opmaak=0,$actie='')
	{
		echo "\n<div class='gegevensblok'>";
		if ($label!="")
		{ echo "\n<div class='labels'>".$label."</div>";}
		echo "\n<div class='invoer'>";

		if ($opmaak!=0)
    {	echo "\n<table style='padding:0px; width:100%; margin:0px;'><tr><td>";}
		echo "\n<textarea class='invoer' rows='".$regels."' id='".$variabele."' name='".$variabele."' ".$actie.">".stripslashes($waarde)."</textarea>";
	  if ($opmaak!=0)
		{ echo "\n</td>";
		  echo "\n<td style='width:20px;'>";
      echo "\n<div style='text-align:center; border:1px solid #E0E0E0; width:15px;'>";
      echo "\n<a href=# class='opmaakknop' onclick='setfontstyle(\"".$variabele."\",1);'><b>B</b></a>";
		  echo "</div>";
			echo "\n<div style='text-align:center; border:1px solid #E0E0E0; width:15px;'>";
      echo "\n<a href=# class='opmaakknop' onclick='setfontstyle(\"".$variabele."\",2);'><i>I</i></a>";
		  echo "</div>";
			echo "\n<div style='text-align:center; border:1px solid #E0E0E0; width:15px;'>";
      echo "\n<a href=# class='opmaakknop' onclick='setfontstyle(\"".$variabele."\",4);'><u>U</u></a>";
		  echo "</div>";
			echo "\n<div style='text-align:center; border:1px solid #E0E0E0; width:15px;'>";
      echo "\n<a href=# class='opmaakknop' title='opmaak verwijderen' onclick='verwijderfontstijlen(\"".$variabele."\",4);'>X</a>";
      echo "</div>";
			echo "\n</td>";
      echo "\n</tr></table>";
    }
		echo "\n</div>";
		echo "\n</div>\n";
	}

  function personencheck($label,$greeks,$checked,$varnaam,$actie)
  { $aantal_personen=count($greeks);
    $regels=round($aantal_personen/3);
    $stijl="style='font-size:8pt; height:20px; padding:0px;'";
    if ($regels*3<$aantal_personen) {$regels++;};
    echo "<div class='gegevensblok'>";
		echo "<div class='labels'>".$label."</div>";
		echo "<div class='invoer' style='padding-left:25px;'>";
		echo "<table style='width:auto;'><tr><td ".$stijl.">";
    $teller=1;
    foreach($greeks as $id=>$naam)
	  { if ($naam!="")
	    { $teller++;
	      $check="";
				if (is_array($checked)) { if (in_array($id,$checked)) {$check="checked";}}
				echo "<input type='checkbox' class='check' ".$stijl." name='".$varnaam.$id."' id='".$varnaam.$id."' value=\"".$id."\" ".$actie." class='check' ".$check.">".$naam."<br>\n";
				if ($teller>$regels)
				{ $teller=1;
				  echo "</td><td ".$stijl.">";
				}
			}
	  }
		echo "</td></tr></table></div></div>";
  }
  function optiescheck($label,$greeks,$checked,$varnaam,$actie)
  { $stijl="style='font-size:8pt; height:20px; padding:0px;'";
    echo "<div class='gegevensblok'>";
		echo "<div class='labels'>".$label."</div>";
		echo "<div class='invoer' style='padding-left:25px;'>";
		echo "<table style='width:auto;'><tr><td ".$stijl.">";
    $teller=0;
    foreach($greeks as $id=>$naam)
	  { if ($naam!="")
	    { $teller++;
	      $check="";
				if (is_array($checked)) { if (in_array($id,$checked)) {$check="checked";}}
				echo "<input type='checkbox' class='check' ".$stijl." name='".$varnaam.$id."' id='".$varnaam.$id."' value=\"".$id."\" ".$actie." class='check' ".$check.">".$naam."<br>\n";
			}
	  }
		echo "</td></tr></table></div></div>";
  }

  function markeer_verplichtinvullen($tabel=0,$kolommen=1)
  { echo "<div class='markeerpijl'>";
    echo "<img src='../figuren/markeerpijl.gif'>";
    echo "</div>";
  }
?>