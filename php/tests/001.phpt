--TEST--
Test stemmer spanish
--SKIPIF--
<?php if (!extension_loaded("stemmer")) print "skip"; ?>
--FILE--
<?php 
$s = stemmer_create("spanish");
echo stemmer_apply($s, "bailando");
?>
--EXPECT--
bail
