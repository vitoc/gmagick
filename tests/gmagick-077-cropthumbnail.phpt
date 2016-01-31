--TEST--
cropthumbnail test
--SKIPIF--
<?php
/* $Id: gmagick-077-cropthumbnail.phpt 280549 2009-05-14 21:45:39Z vito $ */
if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php
$gm = new Gmagick();
$gm->read("magick:rose");
$gm->cropThumbnailImage(3, 3);

//Test the the calculated values are actually correct.
$desired_height = 250;
$imageWidth = 1128;

//Test the the calculated values are actually correct.
$desired_height = 250;
$imageWidth = 1128;
$imageHeight = 1128;

$legacySettings = array(0, 1);

foreach($legacySettings as $legacy) {
	for ($desired_width = 245; $desired_width < 255; $desired_width++) {
		$gmagick = new Gmagick();
		$gmagick->newImage ($imageWidth, $imageHeight, 'blue');

		$gmagick->cropThumbnailImage(
			$desired_width,
			$desired_height,
			$legacy
		);
		$error = false;

		$thumbnailImageWidth = $gmagick->getImageWidth();
		$thumbnailImageHeight = $gmagick->getImageHeight();

		if ($thumbnailImageHeight != $desired_height) {
			echo "Incorrect height for desired_width $desired_width imageHeight $imageHeight".PHP_EOL;
			$error = true;
		}

		$expectedWidth = $desired_width;
		$expectedHeight = $desired_height;

		if ($legacy == true && 
			$desired_width == 250 &&
			$desired_height == 250) {
			// The legacy behaviour is to generate a wrong size for this setting.
			// Thumbnail size of 249 x 250 does not matched desired size 250 x 250 
			// for source image of 1128 x 1128
			$expectedWidth = 249;
		}

		if ($thumbnailImageWidth != $expectedWidth) {
			echo "Unexpected width of $thumbnailImageWidth for desired_width $desired_width, expected width is $expectedWidth".PHP_EOL;
			$error = true;
		}

		if ($thumbnailImageHeight != $expectedHeight) {
			echo "Unexpected height $thumbnailImageHeight for desired_width $desired_width, expected height is $expectedHeight".PHP_EOL;
			$error = true;
		}

		if ($error) {
			printf(
				"Thumbnail size of %d x %d does not matched expected size %d x %d for source image of %d x %d. Legacy is %d\n",
				$thumbnailImageWidth, $thumbnailImageHeight,
				$desired_width, $desired_height,
				$imageWidth, $imageHeight,
				$legacy
			);
		}
	}
}

echo "ok";

?>
--EXPECTF--
ok
