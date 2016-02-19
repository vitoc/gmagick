--TEST--
Test bug 71626 - multiple calls to queryFontMetrics
--SKIPIF--
<?php

if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php

$textWidth = null;

for ($i=0; $i<5; $i++) {
	$image = new Gmagick();
	$fontDraw = new GmagickDraw();
	$fontMetrics = $image->queryFontMetrics($fontDraw, 'g');

	if (is_array($fontMetrics) === false ||
		isset($fontMetrics['textWidth']) === false) {
		echo "fontMetrics contains bad data".PHP_EOL;
		var_dump($fontMetrics);
	}
}


for ($i=0; $i<5; $i++) {
	$gmagick = new \Gmagick("magick:logo");
	$fontDraw = new GmagickDraw();
	$fontMetrics = $image->queryFontMetrics($fontDraw, 'g');

	if (is_array($fontMetrics) === false ||
		isset($fontMetrics['textWidth']) === false) {
		echo "fontMetrics contains bad data".PHP_EOL;
		var_dump($fontMetrics);
	}
}


echo "ok";
?>
--EXPECT--
ok
