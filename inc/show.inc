<?php
  function brm_afsluiten()
	{ echo "<script>top.location='".$_SESSION['root']."inc/brm_afsluiten.php'</script>";
		//echo "script>top.location='".$_SESSION['root']."inc/brm_afsluiten.php'</script";
		exit;
  }
	
  function init_toestel()
  { $test=stristr($_SERVER['HTTP_USER_AGENT'],'iPhone');
    if ($test=="") {$test=stristr($_SERVER['HTTP_USER_AGENT'],'Android');}
    if ($test=="") {$test=stristr($_SERVER['HTTP_USER_AGENT'],'blackberry');}
    if ($test=="") {$test=stristr($_SERVER['HTTP_USER_AGENT'],'iPad');}
//if ($test=="") {$test=stristr($_SERVER['HTTP_USER_AGENT'],'Safari');}
//echo $_SERVER['HTTP_USER_AGENT'];
    //voor testdoeleinden van Joop
    //$test=stristr($_SERVER['HTTP_USER_AGENT'],'Safari');
    if ($test=="" && $_SESSION['user']['uid']==10)
    { if (stristr($_SERVER['HTTP_USER_AGENT'],'chrome')=="")
      { $test=stristr($_SERVER['HTTP_USER_AGENT'],'Safari');}
    }
    $_SESSION['SERVER']=$_SERVER['HTTP_USER_AGENT'];
    $_SESSION['test']=$test;
    if ($test!="")
    { if (stristr($_SERVER['HTTP_USER_AGENT'],'Tablet')!="")
      { $_SESSION['toestel']='tablet';}
      else
      { $_SESSION['toestel']='mobile';}
			$_SESSION['mobile']=true;
			$_SESSION['target0']="";
			$_SESSION['target1']="";
			$_SESSION['target2']="";
			$_SESSION['frame']=""; 
    }
    else
    { $_SESSION['toestel']="pc";
//			$_SESSION['mobile']=false;
			$_SESSION['mobile']=true;
			$_SESSION['target0']="work";
			$_SESSION['target1']="work_left";
			$_SESSION['target2']="work_right";
//			$_SESSION['frame']="_frame";
			$_SESSION['frame']="";
	  }
  }
/*
  function storingstest($pagina,$getvars)
	{ global $q;
	  //sqltest
		echo "<div style='font-size:11pt; padding:20px; border:2 solid red; background-color:white; font-weight:bold;'>";
	  echo "STORING!!!";
	  echo "<br>".$info;
  	echo "<br>Er wordt momenteel aan gewerkt.";
    echo "<br><br>Joop</div>";
	}
*/
	function save_memuse()
	{ global $q, $labels;
		$datum=getdate();
		$dt=$datum['mday']." ".$datum['hours'].":".$datum['minutes'];
		$sql="insert into mem_log (phpscript,memory_use,datum)
		values ('".$labels['pagina']."',".memory_get_usage().",'".$dt."')";
		$q->exec_sql($sql);
	}

  function herstel_session()
  { global $_SESSION, $_COOKIE, $q;

    $pad=realpath('../inc/afbeelden.inc');
    if (strpos($pad,'rm_dev')>0) { $_SESSION['test']=2;} else { $_SESSION['test']=1;}

    $cust_id=$_COOKIE['brm_cust_id'];
    $taal=$_COOKIE['brm'.$cust_id.'_taal'];
    $uid=$_COOKIE['brm'.$cust_id.'_uid'];
    $_SESSION['user']['cust_id']=$cust_id;
	  $_SESSION['user']['taal']=$taal;
	  $_SESSION['user']['uid']=$uid;
    $sql="select bid,cust_id,cust_login,cust_name from 0_customers where cust_id=".$cust_id;
    $q->query($sql);
    if ($q->rowcount>0)
    { $customer=$q->next_record();
      $sql="select uid,pid,cust_id,user,password,bevoegdheid,naam_compleet,inlogdatum,taal, agendaweergave,googleagenda
          from 0_users
          where actief<3 and cust_id=".$cust_id." and uid=".$uid;
		  $q->query($sql);
		  $rec = $q->next_record();
		  $user_name=$rec['user'];
		  init_settings($uid);
			$_SESSION['user']['cust_id']=$rec['cust_id'];
			$_SESSION['user']['bevoegdheid']=$rec['bevoegdheid'];
			$_SESSION['user']['naam']=$rec['user'];
			$_SESSION['user']['naam_compleet']=$rec['naam_compleet'];
			$_SESSION['user']['bid']=$customer['bid'];
			$_SESSION['user']['uid']=$rec['uid'];
			$_SESSION['user']['pid']=$rec['pid'];
			$_SESSION['user']['taal']=$rec['taal'];
			$_SESSION['user']['googleagenda']=$rec['googleagenda'];
			$_SESSION['user']['agendaweergave']=$rec['agendaweergave'];
			$_SESSION['user']['cust_login']=$customer['cust_login'];
			$_SESSION['user']['cust_name']=$customer['cust_name'];
	  }
	}
 
	function sh_title($title)
  {	echo "<div class='tiletitle' style='display:block;'>".ucfirst($title)."</div>";
  }
	function sh_tiletitle($title,$columns=0)
  {	if ($columns==0)
   { echo "<div class='tiletitle'>".ucfirst($title)."</div>";}
   else
   { echo "<div><table><tr><td class='tiletitle' colspan=".$columns.">".ucfirst($title)."</td></tr></table></div>";}
  }
	function sh_grouptitle($title,$columns=0)
  {	if ($columns==0)
   { echo "<div class='grouptitle'>".ucfirst($title)."</div>";}
   else
   { echo "<div><table><tr><td class='grouptitle' colspan=".$columns.">".ucfirst($title)."</td></tr></table></div>";}
  }
	function sh_subgrouptitle($title,$columns=0)
  {	if ($columns==0)
   { echo "<div class='subgrouptitle'>".ucfirst($title)."</div>";}
   else
   { echo "<div><table><tr><td class='subgrouptitle' colspan=".$columns.">".ucfirst($title)."</td></tr></table></div>";}
  }
	function sh_grouptitle_action($titel,$action)
  { $img="<img src='img/play.png'>";
	  echo "<div class='grouptitle'><a href='#' class='grouptitle' onclick=".$action.">".$img." ".ucfirst($titel)."</a></div>";
  }
	function toelichting($tekst)
  { echo "<div class='toelichting'>".nl2br(ucfirst($tekst))."</div>";
  }
	function opmerking($tekst)
  { echo "<div class='opmerking'>".nl2br(ucfirst($tekst))."</div>";
  }

  function actieknop($label,$actie,$target,$waarschuwing="")
  { if ($waarschuwing=="")
    { echo "<a href='".$actie."' target='".$target."'>"; }
    else
    { echo "<a href='".$actie."' target='".$target."' onclick='confirm(\"".$waarschuwing."\")'>"; }
    echo $label."</a>";
  }
  function selectieknop($href,$target,$label='')
  { if ($label=="") { $label=maaklabel('selectie');}
    echo "<div style='font-style:italic; padding-bottom:5px;'>";
		echo "<a href='".$href."' target='".$target."'>".$label." ></a>";
		echo "</div>";
  }

  function sh_layoutcode2html($content)
  { $codes=array("@P@"=>"<p style='page-break-before: always;'> </p>",
                 "@BI@"=>"<b><i>",
                 "@/BI@"=>"</b></i>",
                 "@IB@"=>"<b><i>",
                 "@/IB@"=>"</b></i>",
                 "@B@"=>"<b>",
                 "@/B@"=>"</b>",
                 "@I@"=>"<i>",
                 "@/I@"=>"</i>",
                 "@U@"=>"<u>",
                 "@/U@"=>"</u>",
                 "@BIU@"=>"<b><i><u>",
                 "@/BIU@"=>"</u></i></b>",
                 "@BU@"=>"<b><u>",
                 "@/BU@"=>"</u></b>",
                 "@IU@"=>"<i><u>",
                 "@/IU@"=>"</u></i>");

    foreach($codes as $from=>$to)
    { $content=str_replace($from,$to,$content);}
    return nl2br($content);
  }

  function sh_removelayoutcode($content)
  { $codes=array("@P@"=>"\n",
                 "@BI@"=>"",
                 "@/BI@"=>"",
                 "@IB@"=>"",
                 "@/IB@"=>"",
                 "@B@"=>"",
                 "@/B@"=>"",
                 "@I@"=>"",
                 "@/I@"=>"",
                 "@U@"=>"",
                 "@/U@"=>"",
                 "@BIU@"=>"",
                 "@/BIU@"=>"",
                 "@BU@"=>"",
                 "@/BU@"=>"",
                 "@IU@"=>"",
                 "@/IU@"=>"",
                 "<br>"=>"\n",
                 "<br />"=>"\n");

    foreach($codes as $from=>$to)
    { $content=str_replace($from,$to,$content);}
    return $content;
  }
  function sh_showimage($label,$img,$width)
	{ echo "<div class='labels'>".$label."</div>";
	  if (file_exists("../".$img))
		{	echo "<div><img src='".$img."' style='width:".$width."px;' /></div>";
		}
		else
		{ echo "<div>No image found on: ".$img."</div>";}
	}	
  function sh_showfieldcontent($content)
	{ if ($content!="")
	  { if (strpos("x".$content,'@figuur_')>0)
	    { $fg=explode("@",$content);
	      $fgeg=explode(":",$fg[1]);
				$locatie=$_SESSION['root']."docfiguren/".$_SESSION['user']['cust_id']."/".$fgeg[0];
				$fig=getimagesize($locatie);
				$dpi=96;
				if (count($fgeg)>1) { $dpi=$fgeg[1];}
				$sizeX=$fig[0]*(96/$dpi);
				$sizeY=$fig[1]*(96/$dpi);
	      echo "<img src='".$_SESSION['root']."docfiguren/".$_SESSION['user']['cust_id']."/".$fgeg[0]."' width='".$sizeX."' height='".$sizeY."' >";
	      if (count($fg)>1)
	      { $notes=sh_layoutcode2html($fg[1]);
	        echo "<br>".$notes;
	      }
	    }
	    else
	    { $content=sh_layoutcode2html($content);
        $content=str_replace(chr(13),'',$content);
	  		$ts=explode(chr(10),$content);
				$t1=0;
				$style="";
				while ($t1<count($ts))
				{ if (substr($ts[$t1],0,3)=='@T@')
					{ $t1++;
						$rows=array();
						while (($t1<count($ts)) && (substr($ts[$t1],0,4)!="@/T@"))
						{ $rows[]=$ts[$t1];
							$t1++;
						}
						echo "<br>";
						echo sh_rows2htmltable(0,$rows);
						echo "<br>";
						$t1++;
					}
					else
					{ $summary=false;
						$summnr=0;
						$skiprow=0;
						$val=$ts[$t1];
						if ($val=="<i>" || $val=="<b>" || $val=="<b><i>") { $style=$val; $skiprow=1;}
						if ($val=="</i>" || $val=="</b>" || $val=="</b></i>") { $style=""; $skiprow=1;}
						if ((strpos($val,".")>-1) && (strpos($val,".")<3) && (intval($val)<1))
						{ $summnr=intval(substr($val,0,strpos($val,".")));}
						if ((substr($val,0,1)=="-") || ($summnr>0))
						{ $summary=true;
							if ($summnr>0)
							{ echo "<table class='work'><tr><td style='width:15px; vertical-align:top'>".$style.$summnr.". </td><td>".$style.substr($val,strlen($summnr)+1)."</td></tr></table>";
								$summnr=0;
							}
							else
							{ echo "<table class='work'><tr><td style='width:10px; vertical-align:top'>- </td><td>".$style.substr($val,2)."</td></tr></table>";}
						}
						else
						{ if ($skiprow==0) { echo $val;}
							$summary=false;
						}
						$t1++;
					}
			  }
		  }
		}
  }
  function veldgegevens($tabelcode,$label,$tekst)
	{ if ($tekst!="")
	  { if ($tabelcode==0 || $tabelcode==3) { echo "<table>";}
			echo "<tr><th style='width:100px;'>".$label."</td>";
			echo "<td>".nl2br($tekst)."</td></tr>";
			if ($tabelcode==2 || $tabelcode==3) { echo "</table>";}	
		}
	}
	function veldtekst_weergeven($leeg_afbeelden,$label,$content)
  { if ($leeg_afbeelden==1 || $content!="")
    { echo "\n<div class='gegevensblok'>";
      if ($leeg_afbeelden!=-3)
      { echo "\n<div class='labels'>".$label."</div>"; }
      echo "\n<div class='gegevens'>".nl2br(stripslashes($content))."</div></div>\n";
    }
  }

  function sh_showfield($empty_show,$label,$content)
	{ if ($empty_show==1 || $content!="")
	  { echo "\n<div class='datablock'>";
	    if ($empty_show==-2) {$bold="style='font-weight:bold; padding-top:10px;'";} else {$bold="";}
		  if ($label!="" && $empty_show>-2)
		  { echo "\n<div class='labels'>".$label."</div>";
		    $divclass='content';
		  }
		  else
		  { $divclass="";}
		  echo "\n<div class='".$divclass."' ".$bold.">\n";
      echo sh_showfieldcontent($content);
			echo "</div></div>";
		}
  } 

  function tabel_weergeven($label,$opmaak,$tekst,$style='',$ajax=0)
  { $opm=explode(";",$opmaak);
		$geldcode="";
		$rand="";
		$tablewidth=" style='width:100%'";
		if ($style==0) {$st1=''; $st2='';}
		if ($style==1) {$st1='<i>'; $st2='</i>';}
		if ($style==2) {$st1='<b>'; $st2='</b>';}
		if ($style==3) {$st1='<b><i>'; $st2='</i></b>';}
		if ($opm[1]<2) {$tablewidth="";}
    if ($opm[0]<6) {$opm[0]=8;}
    if ($opm[1]==1) { $rand=' border:0;';}
    if ($opm[1]==3) { $rand=' border:0;';}
    $matrix=string2array($tekst);
    if (is_array($matrix))
    { $matrix=kruistabel($matrix);
      $yn=count($matrix);
      $xn=count($matrix[0]);
      if ($opm[1]>1)
      { if ($xn>0) { $kolom=intval(100/$xn);} else { $kolom=100;}
        $kp="width:".$kolom."%;";
		  }
		  else
		  { $kp="";}
 			echo "<div class='gegevensblok'>";
			if ($label!="")
			{ echo "<div class='labels'>".$label."</div>";
			  echo "<div class='invoer'>";
			}
			echo "<table class='xtabel' ".$tablewidth.">";
			foreach($matrix as $y=>$xreeks)
			{ foreach($xreeks as $x=>$content)
				{ $t=sh_layoutcode2html($content);
/*				  if ($ajax==1)
				  { $t=str_replace(chr(128),"&euro;",$t);
				  }
*/          if ($y==0)
				  { echo "<td class='xtabel".$opm[$x+2]."' style='font-style: italic; font-size:".$opm[0]."pt;".$rand.$kp."'>";}
				  else
				  { echo "<td class='xtabel".$opm[$x+2]."' style='font-size:".$opm[0]."pt;".$rand.$kp."'>";}
				  veldcontent_weergeven($st1.$t.$st2);
				  echo "</td>";
				}
				echo "</tr>";
			}
			echo "</table>";
			if ($label!="") { echo "</div>";}
			echo "</div>";
		}
		else
		{ echo "<div class='gegevensblok'>";
		  echo "<div class='labels'>".$label."</div>";
		  echo "<div class='invoer'>".maaklabel('leeg')."</div>";
		  echo "</div>";
		}
	}

  function haal_rubriek($brontekst,$rubrieknaam)
  {
		if (strpos($brontekst,$rubrieknaam)>-1)
			{
				$A2=substr($brontekst,strpos($brontekst,$rubrieknaam)+strlen($rubrieknaam))."[]";
				$A3=substr($A2,0,strpos($A2,"["));
				while ((strlen($A3)>0) && ((ord(substr($A3,0,1))==13) || (ord(substr($A3,0,1))==10)))
					{$A3=substr($A3,1);}
				while ((strlen($A3)>0) && ((ord(substr($A3,strlen($A3),1))==13) || (ord(substr($A3,strlen($A3),1))==10)))
					{$A3=substr($A3,0,strlen($A3)-1);}
			}
		else
			{$A3="";}
		$ts=explode(chr(13).chr(10),$A3);
		$tr=array();
		while (list($k,$v)=each($ts))
		{ if ($v!="") { $tr[]=$v;}}
		return implode(chr(13).chr(10),$tr);
  }

  function float2decimaal($gf)
  { $n=explode(".",$gf);
    $gd=$n[0];
    if ((count($n)==2) && ($n[1]>0))
    { $n1=intval($n[1]/10);
      if (strval(10*$n1)!=strval($n[1]))
      { $n1=substr($n[1],0,2);}
			$gd.=",".$n1;
		}
    return $gd;
  }

  function sh_rows2htmltable($kantlijn,$rows)
  { $tr="";
    $geld=array();
    $totalen=array();
    $opmaak="";
    $start=0;
    $fsize="8pt";
    //rij met kolomlabels
    if (substr($rows[$start],0,6)=="@style")
    { $rs=$rows[$start];
      str_replace(chr(10),"",$rs);
			str_replace(chr(13),"",$rs);
			$opmaak=substr($rs,7);
      $kx=explode(";",$opmaak);
      $fsize=strval($kx[0]-2)."pt";
      $uitl=$kx;
      $start++;
    }
    if ($kx[1]=="0") {$randen="border:solid 1px gray; width:auto;";}
    if ($kx[1]=="1") {$randen="border:0; width:auto;";}
    if ($kx[1]=="2") {$randen="border:solid 1px gray; width:100%;";}
    if ($kx[1]=="3") {$randen="border:0; width:100%;";}

    $tr.="<table class='tabel' style='".$randen.";'><tr>";
    if ($kantlijn>0)
    { $tr.="<td width=".$kantlijn."> </td>";}

    $uitlijning[0]="style='text-align:left; font-size:".$fsize.";".$randen.";'";
    $uitlijning[1]="style='text-align:center; font-size:".$fsize.";".$randen.";'";
    $uitlijning[2]="style='text-align:right; font-size:".$fsize.";".$randen.";'";

    $k=explode(";",$rows[$start]);
    while (list($key,$var)=each($k))
		{ $uitlijncode=intval($uitl[$key+2]);
		  if ($uitlijncode=="")
		  { if ($key==0)
		    { $uitlijncode="0";}
		    else
		    { $uitlijncode="1";}
		  }
		  $tr.='<th class=\'tabel\' '.$uitlijning[$uitlijncode].'>'.$var.'</th>';
		  $geld[$key]="";
		  $totalen[$key]=0;
		}
	  $start++;
		$tr.='</tr>';
    for ($t1=$start; $t1<count($rows); $t1++)
    { $k=explode(";",$rows[$t1]);
			$tr.='<tr>';
			if ($kantlijn>0)
			{ $tr.="<td width=".$kantlijn." ".$randen."> </td>";}
			while (list($key,$var)=each($k))
			{ $uitlijncode=intval($uitl[$key+2]);
			  $var=trim($var);
			  if (substr($var,0,8)=='@figuur_')
			  { $fg=explode("@",substr($var,1));
					$fgeg=explode(":",$fg[0]);
					$locatie="../docfiguren/".$_SESSION['user']['cust_id']."/".$fgeg[0];
					$fig=getimagesize($locatie);
					$dpi=96;
					if (count($fgeg)>1) { $dpi=$fgeg[1];}
					$sizeX=$fig[0]*(96/$dpi);
					$sizeY=$fig[1]*(96/$dpi);
					$var="<img src='../docfiguren/".$_SESSION['user']['cust_id']."/".$fgeg[0]."' width='".$sizeX."' height='".$sizeY."' >";
					if (count($fg)>1)
					{ $var.="<br>".$fg[1];}
			  }
			  else
			  {
					if ($t1<count($rows)-1)
					{ if ($var[0]=="€")
						{ $totalen[$key]+=intval(substr($var,1));}
						else
						{ $totalen[$key]+=intval($var);}
					}
					if ((is_numeric(substr($var,-1,1))==false && $var[0]!="+") && ($opmaak==""))
					{ $uitlijncode="0";}
					else
					{ if ($var[0]=="€" || $var[0]=="$")
						{ $geld[$key]=$var[0]." ";
							if ($opmaak=="") {$uitlijncode="2";}
						}
						else
						{ if ($opmaak=="") {$uitlijncode="1";} }
					}
					if (($t1==count($rows)-1) && ($var=="+"))
					{ $var=$geld[$key].$totalen[$key];
						if (($opmaak=="") && ($geld[$key]!=""))
						{ $uitlijncode="2";}
					}
			  }
        $tr.="<td class='tabel' ".$uitlijning[$uitlijncode].$var."</td>";
			}
			$tr.="</tr>";
		}
		$tr.="</table>";
    return $tr;
  }

  function figuur_weergeven($maxWidth,$maxHeight,$bestand,$dpi)
  {	if (strpos($_SESSION['root'],"rm_dev")>0) 
	  { $pad=$_SERVER['DOCUMENT_ROOT']."/rm_dev/".$bestand;}
	  else
		{ $pad=$_SERVER['DOCUMENT_ROOT']."/rm/".$bestand;}
	  if (file_exists($pad))
	  { $fig=getimagesize($pad);
			if ($fig[2]==1 || $fig[2]==2 || $fig[2]==3)
			{ if ($dpi<96) { $dpi=96;}
				$sizeX=$fig[0]*(96/$dpi);
				$sizeY=$fig[1]*(96/$dpi);
				$verhouding=$sizeY/$sizeX;
				while ($sizeY>$maxHeight || $sizeX>$maxWidth)
				{ $sizeX--;
					$sizeY=$verhouding*$sizeX;
				}
				echo "<a href='".$_SESSION['root'].$bestand."' target='figuurafbeelding'><img src='".$_SESSION['root'].$bestand."' height='".$sizeY."' width='".$sizeX."' border=0></a>";
			}
		}
		else
		{ echo "geen figuur";}
  }
	function lijst($titel,$sqltekst,$pad,$naam,$kolommen=1)
	{ global $q;
	  $q->query($sqltekst);
		if ($q->rowcount>0)
		{ $_SESSION['verwijderbaar']=1;
	    echo "<div class='gegevensblok'>"; 
      groeptitel($titel);
			if ($kolommen>1)
      { $breedte=strval(100/(1+$kolommen))."%";
        echo "<table class='lijstkolommen'>";
				while ($row=$q->next_record())
			  { echo "<tr>";
			    for ($t1=1; $t1<=$kolommen; $t1++)
					{ $geg=$row['data'.$t1];
						if (strlen($geg)==8 && strval($geg)>0)
						{ $geg=datumtekst($geg);}
						echo "<td class='lijstkolom".$t1."' style='padding-right:5px;'>";
						echo "<a href='#' onclick='ganaar(1,\"".$pad."\",\"".$naam."\",".$row['id'].",0);'>".$geg."</a>";
						echo "</td>";
					}
					echo "</tr>";
        }
        echo "</table>";
      }
			else
			{ echo "<table class='lijstkolommen'>";
			  while ($row=$q->next_record())
			  { $geg=$row['data1'];
				  echo "<tr><td class='lijstkolom1' style='width:100%;'>";
					echo "<a href='#' onclick='ganaar(1,\"".$pad."\",\"".$naam."\",".$row['id'].",0);'>".$geg."</a>";
			    echo "</td></tr>";
			  }
				echo "</table>";
			}
			echo "</div>";
		}
	}

  function salarisoverzicht($label,$salaris)
  { global $maanden,$jaar;
  	$sjaren=explode(chr(10),$salaris);
		echo "<div class='gegevensblok'>";
		echo "<div class='labels'>".$label."</div>";
		echo "<div class='invoer'>";
		$mn=$maanden[$_SESSION['user']['taal']];
		$st="style='font-size:7pt;'";
		{ echo "<table style='width:auto;'><tr><th ".$st.">".$jaar[$_SESSION['user']['taal']]."</th>";
		  while (list($k,$m)=each($mn)) { echo "<th ".$st.">".substr($m,0,3)."</th>";}
		  echo "</tr>";
		  while (list($key,$var)=each($sjaren))
		  { $sreeks=explode(";",$var);
			  echo "<tr>";
			  echo "<td ".$st."><i>".$sreeks[0]."</i></td>";
			  $bruto=$sreeks[1];
			  for ($t1=1; $t1<13; $t1++)
			  { if ($t1<count($sreeks))
				  { $bruto=$sreeks[$t1];}
				  echo "<td ".$st.">".$bruto."</td>";
			  }
			  echo "</tr>";
		  }
		  echo "</table>"; 
		}
		echo "</div></div>";
	}

  function bijlagenaam($b)
  { $bs=basename($b);
    $ts=explode("_",$bs);
    if (count($ts)>1)
    { return $ts[1];}
    else
    { return $bs;}
  }

	function celopmaak($tekst)
	{ $rows=explode(chr(13).chr(10),$tekst);
		$ts="";
		$summary=0;
		foreach($rows as $var)
		{ if (substr($var,0,2)=="- ")
			{ if ($summary==0) { $ts="<ul class='acties'>"; $summary++;}
				$ts.="<li class='acties'>".substr($var,2)."</li>";
			}
			else
			{ if ($summary==1) { $ts.="</ul>"; $summary=0;}
				$ts.=$var."<br>";
			}
		}
		if ($summary==1) { $ts.="</ul>";}
		return $ts;
  }
	function toon_filter($seltekst)
	{ if (count($seltekst)>0)
		{ echo "<div class='gegevensblok'>";
			$filter="Filter:";
			echo "<table>";
			foreach($seltekst as $key=>$var)
			{ echo "<tr><td class='toelichting' style='padding:2px;'>".$filter."</td>";
		    echo "<td class='toelichting' style='padding:2px;'>".$var['label'].": </td><td class='toelichting' style='padding:2px;'>".$var['content']."<td></tr>";
		    $filter="";
			}
			echo "</table>";
			echo "</div><hr>";
		}
	}
?>
