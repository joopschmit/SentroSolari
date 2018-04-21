 <?php
  session_start();
	$nid=$_GET['id'];
	$language=$_SESSION['language'];
  
	include('../inc/show.inc');
	include('../inc/show_input.inc');
  include('../classes/class_labels.php');
	include('../classes/class_news.php');

  $news=new seso_news($language);
  $labels=new seso_labels("news_edit",$language);

  echo "<script>
	  nid=".$nid.";
		function save_news(field,language)
		{ f=field.name;
		  v=field.value;
			test=1;
			if (f=='nimagewidth_0' && (v<10 || v>1500)) 
			{ alert('".$labels->getlabel('wrongimagesize')."'); test=0;}
			if (test==1)
			{	$.post('news/news_save.php',{id:nid,language:language,f:f,v:v},
					function() 
					{ if (f=='nimagewidth_0') 
					  { $('#nimage').load('news/news_img.php?id='+nid);
					  }
					}
			  );
			}
		}
		function get_image(field)
		{ $('#imgform').submit();
	  }
		function removeimage()
		{ if (confirm('".$labels->getlabel('removeimgwarning')."'))
		  { $.get('news/news_imgremove.php?id=".$nid."',
		    function() { $('#nimage').html(' ');});
		  }	
    }
		$('#upload').on('click', function() {
			var file_data = $('#newsimage').prop('files')[0];   
			if (typeof file_data !== 'undefined')
			{ var form_data = new FormData(); 
				form_data.append('file', file_data);
				$.ajax({
						url: 'news/upload.php?id=".$nid."', // point to server-side PHP script 
						dataType: 'text',  // what to expect back from the PHP script, if anything
						cache: false,
						contentType: false,
						processData: false,
						data: form_data,                         
						type: 'post',
						success: function(answr){ 
							if (answr==1)
							{ $('#nimage').load('news/news_saveimage.php?id=".$nid."&f=nimage&v=".$nid."_'+file_data['name']);}
							else
							{	alert(answr);}
						}
				 });
		  }
			else
			{	alert('no file selected');}			
		});

	</script>"; 
	
	
  $item=$news->getnewsitem($nid);
	$action="onchange='save_news(this);'";

  echo "<div class='container'>";
  echo "<div class='mainmenutile'>";
  
	echo "<div class='datablock'>";	

  //VAR VALUE
	sh_title($labels->getlabel('newsitem')." - ".$item[$language]['nitem']); 
	foreach($item as $lang=>$var)
	{ echo "<br>";
		shi_inputfield($labels->getlabel('item')." ".$labels->languages[$lang],"nitem_".$lang,$var['nitem'],254,$action);
		shi_inputtext($labels->getlabel('text')." ".$labels->languages[$lang],"ntext_".$lang,$var['ntext'],10,$action);
	}	
	echo "</div>";
	
	sh_title($labels->getlabel('image'));
	echo "<div id='nimage'>";
	if ($item[0]['nimage']!="")
	{ $newsimage="news/img/".$item[0]['nimage'];
    $imgsize=getimagesize("../".$newsimage);
    echo "<img src='".$newsimage."' style='text-align:left;width:".$item[0]['nimagewidth']."px;'>";
    echo "<div class='data'>";
	  echo "<div class='data'>".$labels->getlabel('imgsize').": ".$imgsize[0]." x ".$imgsize[1]."</div>";
	  echo "<a class='submenu' href='#' onclick='removeimage();'><img src='img/play.png' /> ".$labels->getlabel('removeimage')."</a>";
    echo "</div>";
	}
  echo "</div>";

	echo "<div class='datablock'>";	
	echo "<div class='labels'>".$labels->getlabel('selectimage')."</div>";
	echo "<div class='data'>";
	echo "<input class='file' id='newsimage' type='file' name='newsimage' />";
	echo "</div>";
//	echo "<button style='padding:5px;' id='upload'>".$labels->getlabel('upload')."</button>";
	echo "<div class='data'>";
	echo "<a class='submenu' id='upload' ".$labels->getlabel('removeimage')."><img src='img/play.png'> ".$labels->getlabel('upload')."</a>";
	echo "</div>";
  shi_inputfield($labels->getlabel('imagewidth')." (10-1500)",'nimagewidth_0',$item[0]['nimagewidth'],4,$action);		 
	foreach($item as $lang=>$var)
	{ echo "<br>";
		shi_inputtext($labels->getlabel('imagetext')." ".$labels->languages[$lang],"nsubtext_".$lang,$var['nsubtext'],1,$action);
	}	

	echo "</div><br></div></div>";
	
?>