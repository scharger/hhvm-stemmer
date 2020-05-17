--TEST--
Test stemmer spanish
--SKIPIF--
<?php if (!extension_loaded("stemmer")) print "skip"; ?>
--FILE--
<?php 
echo hh_stem("spanish", "bailando");
?>
--EXPECT--
bail
