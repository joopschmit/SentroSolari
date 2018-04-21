
	var invoer='';
	var mon='';
	function codeinvoer1(code)
	{ alert(invoer.length);
	}
	function codeinvoer(code)
	{ if (code=='#') { top.location='index.php';}
		if (code=='C') { invoer=''; mon=' ';} 
		else 
		{ invoer+=code; mon+=' &bull; ';
		}
		$('#monitor').html(mon);
		if (invoer.length==5)
		{ $('#subtitel').html('Bezig met starten...');
			$.ajax(
			{ type:'POST', url:'inlogcheck.php', data:'code='+invoer,
				success: function(data) {
					if (data==0) { alert('foute code: '+invoer); invoer=''; mon=''; $('#monitor').html(''); $('#subtitel').html('');}
					if (data==5) { top.location='brm.php';	}
				}
			});
		}
	}
