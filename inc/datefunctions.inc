<?php
date_default_timezone_set('Europe/Amsterdam');
  function dagen_per_maand($mnd,$jr)
  { $reeks=array(31,28,31,30,31,30,31,31,30,31,30,31);
    $aantal=$reeks[intval($mnd)];
    if ((intval($mnd)==1) & (round($jr/4)*4 == $jr))
      {$aantal=29;}
    return $aantal;
  }

  function datetext($datecode,$year=4)
  { if (strlen($datecode)>7)
    { $dt=substr($datecode,6,2)."-".substr($datecode,4,2);
	    $yr=substr($datecode,0,4);
			if($year==4) { $dt.="-".$yr;}
			if ($year==2) { $dt.="-".substr($yr,2,2);}
		}
    else
    { $dt="";}
    return $dt; 
  }

  function timetext($datecode)
  { $dt=substr($datecode,8,2).".".substr($datecode,10,2);
    return $dt;
  }

  function tijdcijfer2urenminuten($tijdcijfer)
  { $tijdcijfer=str_replace(",",".",$tijdcijfer);
	  $uren=intval($tijdcijfer);
    $ts=$tijdcijfer-$uren;
    if ($ts>0)
    { $minuten=intval($ts*61); }
    else
    { $minuten=0;}
    $tijd=array();
    $tijd[0]=$uren;
    $tijd[1]=$minuten;
    $tijd[2]=strval($uren)." uren en ".strval($minuten)." minuten";
    return $tijd;
  }

  function urenminuten2tijdcijfer($uren,$minuten)
  { $u=intval($uren);
    if ($minuten>0)
    { $ts=(intval(($minuten*100)/60)/100);
      $u+=$ts;
    }
    return $u;
  }

  function dagnummer($datumcode)
	{ $dag=date('w', mktime(0,0,0,intval(substr($datumcode,4,2)),intval(substr($datumcode,6,2)),intval(substr($datumcode,0,4))));
		return $dag;
	}
  function dagnaam($datumcode)
	{ global $dagen;
		$dag=date('w', mktime(0,0,0,intval(substr($datumcode,4,2)),intval(substr($datumcode,6,2)),intval(substr($datumcode,0,4))));
		return $dagen[$_SESSION['user']['taal']][$dag];
	}
  function weekend($datumcode)
	{ $dag=date('w', mktime(0,0,0,intval(substr($datumcode,4,2)),intval(substr($datumcode,6,2)),intval(substr($datumcode,0,4))));
		if (($dag==0) || ($dag==6)) { return true;} else { return false;}
	}
  function maandnaam($lengte,$datumcode)
	{ global $maanden;
		$mnd=intval(substr($datumcode,4,2));
		if ($lengte==0)
		{ return $maanden[$_SESSION['user']['taal']][$mnd-1];}
		else
		{ return substr($maanden[$_SESSION['user']['taal']][$mnd-1],0,$lengte);}
	}

  function datumnaam($datumcode,$kort=0)
	{	$ts="";
	  if ($kort==0) { $ts=dagnaam($datumcode)." ";}
	  $ts.=intval(substr($datumcode,6,2))." ".maandnaam(0,$datumcode)." ".substr($datumcode,0,4);
	  return $ts;
	}

  function actualdate()
	{ global $maanden, $dagen;
		$vandaag = getdate();
		$dag  = $vandaag['mday'];
		$wdag = $vandaag['wday'];
		$maand = $vandaag['mon'];
		return $dagen[$_SESSION['user']['taal']][intval($wdag)]." ".$dag." ".$maanden[$_SESSION['user']['taal']][intval($maand)-1]." ".$vandaag['year'];
	}

  function maak_datumtijdcode($jaar,$maand,$dag,$uur,$minuten)
  { if (strlen($jaar)==2) { if (intval($jaar)<30) { $jaar="20".$jaar;} else { $jaar="19".$jaar;}}
    //return strval(intval($jaar)*100000000+intval($maand)*1000000+intval($dag)*10000+intval($uur)*100+intval($minuten));
    return strval($jaar).substr('0'.strval($maand),-2,2).substr('0'.strval($dag),-2,2).substr('0'.strval($uur),-2,2).substr('0'.strval($minuten),-2,2);
  }

  function maak_datumcode($jaar,$maand,$dag)
  { if (strlen($jaar)==2) { if (intval($jaar)<30) { $jaar="20".$jaar;} else { $jaar="19".$jaar;}}
//    return strval(intval($jaar)*10000+intval($maand)*100+intval($dag));
    return strval($jaar).substr('0'.strval($maand),-2,2).substr('0'.strval($dag),-2,2);
  }

  function datum2datumcode($datum)
  { if ($datum!="")
	  { $dat=explode("-",$datum);
		  if (count($dat)==1) { $datum='01-01-'.$datum;}
		  if (count($dat)==2) { $datum='01-'.$datum;}
		  $dat=explode("-",$datum);
		  return maak_datumcode($dat[2],$dat[1],$dat[0]);
		}
		else
		{ return "";}
	}

  function actualdatecode()
	{ date_default_timezone_set('Europe/Amsterdam');
	  $vandaag = getdate(); 
		$jaar = $vandaag['year'];
		$dag  = $vandaag['mday'];
		$maand = $vandaag['mon'];
		$uur = $vandaag['hours'];
		$minuten = $vandaag['minutes'];
		return maak_datumtijdcode($jaar,$maand,$dag,$uur,$minuten);
   }

  function dag_terug($datumcode)
  { $uur=intval(substr($datumcode,8,2));
    $minuten=intval(substr($datumcode,10,2));
    $dag=intval(substr($datumcode,6,2))-1;
    $maand=intval(substr($datumcode,4,2));
    $jaar=intval(substr($datumcode,0,4));
    if ($dag<1)
    { $maand=intval(substr($datumcode,4,2))-1;
      if ($maand<1)
      {
       $maand=12;
       $jaar=$jaar-1;
      }
      $dag=dagen_per_maand($maand-1,$jaar);
    }
    $datumcode=maak_datumtijdcode($jaar,$maand,$dag,$uur,$minuten);
    return $datumcode;
  }

  function week_terug($datumcode)
	{ $dag=intval(substr($datumcode,6,2))-7;
		$maand=intval(substr($datumcode,4,2));
		$jaar=intval(substr($datumcode,0,4));
		if ($dag<1)
		{	$maand=intval(substr($datumcode,4,2))-1;
			if ($maand<1)
			{ $maand=12;
			  $jaar=$jaar-1;
			}
			$dag=dagen_per_maand($maand-1,$jaar)-6;
		}
		return maak_datumcode($jaar,$maand,$dag);
	}

  function week_vooruit($datumcode)
  { $dag=intval(substr($datumcode,6,2))+7;
    $maand=intval(substr($datumcode,4,2));
    $jaar=intval(substr($datumcode,0,4));
    $dpm=dagen_per_maand($maand-1,$jaar);
    if ($dag>$dpm)
    { $maand=intval(substr($datumcode,4,2))+1;
      if ($maand>12)
      { $maand=1;
        $jaar=$jaar+1;
      }
      $dag=$dag-$dpm;
    }
    return maak_datumcode($jaar,$maand,$dag);
  }

  function dag_vooruit($datumcode)
  { $uur=intval(substr($datumcode,8,2));
    $minuten=intval(substr($datumcode,10,2));
    $dag=intval(substr($datumcode,6,2))+1;
    $maand=intval(substr($datumcode,4,2));
    $jaar=intval(substr($datumcode,0,4));
    if ($dag>dagen_per_maand($maand-1,$jaar))
    { $maand=intval(substr($datumcode,4,2))+1;
      if ($maand>12)
      {
       $maand=1;
       $jaar=$jaar+1;
      }
      $dag=1;
    }
    if (strlen($datumcode)>8)
    { return maak_datumtijdcode($jaar,$maand,$dag,$uur,$minuten);}
    else
    { return maak_datumcode($jaar,$maand,$dag);}
  }

  function uur_vooruit($datumcode)
  { $uur=intval(substr($datumcode,8,2))+1;
    $minuten=intval(substr($datumcode,10,2));
    if ($uur>23)
    { $datumcode=dag_vooruit($datumcode);
      $uur=0;
    }
    $dag=intval(substr($datumcode,6,2));
    $maand=intval(substr($datumcode,4,2));
    $jaar=intval(substr($datumcode,0,4));
    return maak_datumtijdcode($jaar,$maand,$dag,$uur,$minuten);
  }
  function jaar_aanpassen($datumcode,$aantal)
	{ $dag=intval(substr($datumcode,6,2));
    $maand=intval(substr($datumcode,4,2))-$aantal;
    $jaar=intval(substr($datumcode,0,4));
		$jaar+=$aantal;
		return maak_datumcode($jaar,$maand,$dag);
  }
  function maanden_terug($datumcode,$aantal)
  { $dag=intval(substr($datumcode,6,2));
    $maand=intval(substr($datumcode,4,2))-$aantal;
    $jaar=intval(substr($datumcode,0,4));
    while ($maand<1)
    { $maand=12+$maand;
      $jaar=$jaar-1;
    }
    while ($dag>dagen_per_maand($maand-1,$jaar))
    {$dag=$dag-1;}
    if (strlen($datumcode)>8)
    { $uur=intval(substr($datumcode,8,2));
      $minuten=intval(substr($datumcode,10,2));
      return maak_datumtijdcode($jaar,$maand,$dag,$uur,$minuten);
    }
    else
    { return maak_datumcode($jaar,$maand,$dag);}
  }

  function maanden_vooruit($datumcode,$aantal)
  { $dag=intval(substr($datumcode,6,2));
    $maand=intval(substr($datumcode,4,2))+$aantal;
    $jaar=intval(substr($datumcode,0,4));
    while ($maand>12)
    { $maand-=12;
      $jaar++;
    }
    while ($dag>dagen_per_maand($maand-1,$jaar))
    {$dag=$dag-1;}
    if (strlen($datumcode)>8)
    {	$uur=intval(substr($datumcode,8,2));
      $minuten=intval(substr($datumcode,10,2));
      return maak_datumtijdcode($jaar,$maand,$dag,$uur,$minuten);
    }
    else
    { return maak_datumcode($jaar,$maand,$dag);}
  }

  function googledatum2datumcode($dt)
  { //google format: 2013-11-05T15:00:00.000+01:00
    if ($dt!="")
    { $datumcode=substr($dt,0,4).substr($dt,5,2).substr($dt,8,2).substr($dt,11,2).substr($dt,14,2);}
    else 
    { $datumcode="";}
    return $datumcode;    
  }
?>
