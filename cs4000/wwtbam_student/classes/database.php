<?php

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Description of database
 *
 * @author joe
 */
class database {

    //put your code here
    public function __construct($uname, $pwd, $host, $database) {
        $this->conn = mysql_connect($host, $uname, $pwd) or die("Cannot connect");
        mysql_select_db($database, $this->conn) or die("invalid database");
    }

    public function query($query) {
        try
        {
            $res = mysql_query($query);
            return $res;
        }
        catch (Exception $e)
        {
            echo $e->getMessage();
        }
    }
    public function get_rows_affected()
    {
        return mysql_affected_rows($this->conn);
    }

}

?>
