--TEST--
Test bug 63677 - getimagehistogram
--SKIPIF--
<?php

if(!extension_loaded('gmagick')) die('skip');
?>
--FILE--
<?php

class Image
{
    private $gmagick;
    private $layers;

    public function __construct(\Gmagick $gmagick)
    {
        $this->gmagick = $gmagick;
        $this->layers = new Layers($this, $this->gmagick);
    }

    public function __destruct()
    {
        if (null !== $this->gmagick && $this->gmagick instanceof \Gmagick) {
            $this->gmagick->clear();
            $this->gmagick->destroy();
        }
    }

    public function histogram()
    {
        return array_map(
            function(\GmagickPixel $pixel) {
                return new \stdClass();
            },
            $this->gmagick->getimagehistogram()
        );
    }
}

class Layers
{
    private $image;
    private $resource;

    public function __construct(Image $image, \Gmagick $resource)
    {
        $this->image = $image;
        $this->resource = $resource;
    }
}


for ($i=0; $i<5; $i++) {
    $image = new Image(new \Gmagick("magick:logo"));
    // the same fixture must beloaded twice to reprodcue the seg fault
    $image = new Image(new \Gmagick("magick:logo"));

    $image->histogram();
}

echo "ok";
?>
--EXPECT--
ok
