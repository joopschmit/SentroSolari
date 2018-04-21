<?php
//session_start();
// MySQLI-database object 2017
// Database Moving Values, Business Relation Manager

class db_joop {
	var $host     = "localhost";
	var $database = "moval_seso";
	var $user     = "moval_seso";  
	var $password = "js190449";

  var $row;
	var $rowcount;
	var $errno = 0;
	var $error = "";
	var $error1 = "";
	var $link_id = null;
	var $query_id = 0;

	
	function __construct($query = "") 
	{	$this->query($query);
	}

	function connect() 
	{ if ($this->link_id==null) 
		{ $this->link_id = @mysqli_connect($this->host,$this->user,$this->password,$this->database);
		  if (!$this->link_id) 
		  { $this->error1 = "connect(): mysqli_connect failed\n";
			  return 0;
		  }
		}
		if (!@mysqli_select_db($this->link_id,$this->database)) 
		{	$this->error = "connect(): mysqli_select_db failed\n";
		  return 0;
		}
  	mysqli_query($this->link_id,"SET NAMES 'latin1'");
		return $this->link_id;
	}

	function free() {
		@mysqli_free_result($this->query_id);
		$this->query_id = 0;
	}

	function query($sql) {
		if ($sql == "") {
			return 0;
		}
		if (!$this->connect()) {
			return 0;
		}
		if ($this->query_id) {
			$this->free();
		}
    $this->query_id = @mysqli_query($this->link_id,$sql);
		$this->row = 0;
		$this->rowcount = @mysqli_num_rows($this->query_id);
		$this->errno = mysqli_errno($this->link_id);
		$this->error = mysqli_error($this->link_id);
		return $this->query_id;
	}

	function next_record() {
		if (!$this->query_id) {
			return 0;
		}
		$ret = @mysqli_fetch_array($this->query_id,MYSQLI_ASSOC);
		$this->row++;
		$this->errno = mysqli_errno($this->link_id);
		$this->error = mysqli_error($this->link_id);
		$stat = is_array($ret);
		if (!$stat) {
			$this->free();
		}
		return $ret;
	}

	function exec_sql($sql)
	{	if (!$this->query($sql)) {
			return 0;
		}
		return $this->next_record();
	}

	function table_names()
	{ $sql="SELECT table_name,table_rows,update_time,data_length,avg_row_length  
		FROM INFORMATION_SCHEMA.TABLES
		where table_schema='moval_seso'"; 
		$this->query($sql);
		while ($row=$this->next_record())
		{ $tables[]=$row;
		}
		return $tables;
	}
	function column_names($table_name)
	{ $sql="SHOW COLUMNS FROM ".$table_name;
		$this->query($sql);
		$n=1;
		while ($row=$this->next_record())
		{ $columns[$n]['veld']=$row['Field'];
		  $columns[$n]['type']=$row['Type'];
		  $n++;
		}
		return $columns;
	}
	function new_id($tabel,$idveld)
	{ $sql="select max(".$idveld.") as id from ".$tabel;
	  $this->query($sql);
		$row=$this->next_record();
		return $row['id']+1;
	}	
	function get_record($tabel,$idnaam,$idwaarde,$velden)
	{ $row=array();
	  $sql="select ".$idnaam.",".$velden." from ".$tabel." where ".$idnaam."=".$idwaarde;
	  $this->query($sql);
		if ($this->rowcount>0) { $row=$this->next_record();} else {$row=array();}
		return $row;
	}	
	function get_recordreeks($tabel,$idnaam,$idreeks,$veld)
	{ $reeks=array();
	  $sql="select ".$idnaam.",".$veld." from ".$tabel." where ".$idnaam." in (".$idreeks.")";
	  $this->query($sql);
		if ($this->rowcount>0) { while ($row=$this->next_record()) { $reeks[$row[$idnaam]]=$row[$veld];}} else {$reeks=array();}
		return $reeks;
	}	
	function get_languages($language)
	{ $ls=array();
	  $sql="select * from seso_labels where name like 'language%' and language=".$language." and kind=1 order by name desc";
    $this->query($sql);
    while($row=$this->next_record())
    { $nr=substr($row['name'],8); 
	    $ls[$nr]=$row['text'];
    }
    return $ls;
  } 		
}
?>