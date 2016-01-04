--TEST--
Gmagick::setImagePage test
--SKIPIF--
<?php
require_once(dirname(__FILE__) . '/skipif.inc');

checkClassMethods(
    'Gmagick',
    array('setImagePage', 'getImagePage')
);

?>
--FILE--
<?php
$image = new Gmagick('magick:rose');
$image->setImagePage(10,10,10,10);
$result = $image->getImagePage();
if (($result['width'] === 10) && ($result['height'] === 10) 
    && ($result['x'] === 10) && ($result['y'] === 10)) {
    echo "ok";
}
?>
--EXPECTF--
ok