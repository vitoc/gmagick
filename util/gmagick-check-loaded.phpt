--TEST--
Check that GMagick is actually loaded
--SKIPIF--

--FILE--
<?php

// The tests are all skipped if gmagick is not loaded. This can lead
// to a false green build when GMagick isn't actually loaded. So 
// this script gives an error to allow us to error before running the tests.
if (extension_loaded("gmagick")) {
	echo "OK" . PHP_EOL;
}
else {
	echo "gmagick module is not loaded." . PHP_EOL;
}

?>
--EXPECTF--
OK