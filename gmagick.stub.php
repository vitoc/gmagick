<?php
/** @generate-function-entries */
/** @generate-legacy-arginfo */
/** @generate-class-entries */

class Gmagick {
	public function __construct(?string $filename = null) {}
	public function __tostring(): string {}

	public function readimage(string $filename): Gmagick {}
	/** @alias Gmagick::readimage */
	public function read(string $filename): Gmagick {}
	/**
	 * @param resource $filehandle
	 */
	public function readimagefile($filehandle, ?string $filename = null): Gmagick {}
	public function writeimage(string $filename, bool $all_frames = false): Gmagick {}
	/** @alias Gmagick::writeimage */
	public function write(string $filename, bool $all_frames = false): Gmagick {}
	/**
	 * @param resource $filehandle
	 */
	public function writeimagefile($filehandle, ?string $format = null): Gmagick {}
	public static function getversion(): array {}
	public function annotateimage(GmagickDraw $drawing_wand, float $x, float $y, float $angle, string $text): Gmagick {}
	public function blurimage(float $radius, float $sigma): Gmagick {}
#if GMAGICK_LIB_MASK >= 1003007
	public function setcompressionquality(int $quality): Gmagick {}
#endif
#if GMAGICK_LIB_MASK >= 1005000
	public function getimagematte(): int {}
#endif
#ifdef GMAGICK_HAVE_SET_IMAGE_PAGE
	public function setimagepage(int $width, int $height, int $x, int $y): bool {}
	public function getimagepage(): array {}
#endif
	public function thumbnailimage(int $width, int $height, bool $fit = false, bool $legacy = false): Gmagick {}
	public function resizeimage(int $width, int $height, int $filter, float $blur, bool $fit = false, bool $legacy = false): Gmagick {}
	public function clear(): Gmagick {}
	public function cropimage(int $width, int $height, int $x, int $y): Gmagick {}
	public function cropthumbnailimage(int $width, int $height): Gmagick {}
	public function coalesceimages(): Gmagick {}
	public function compositeimage(Gmagick $source, int $COMPOSE, int $x, int $y): Gmagick {}
	public function addimage(Gmagick $source): Gmagick {}
	public function addnoiseimage(int $noise_type): Gmagick {}
	public function borderimage(GmagickPixel|string $color, int $width, int $height): Gmagick {}
	public function thresholdimage(float $threshold, int $channel = Gmagick::CHANNEL_DEFAULT): bool {}
	public function charcoalimage(float $radius, float $sigma): Gmagick {}
	public function chopimage(int $width, int $height, int $x, int $y): Gmagick {}
	public function commentimage(string $comment): Gmagick {}
	public function current(): Gmagick {}
	public function cyclecolormapimage(int $displace): Gmagick {}
	public function deconstructimages(): Gmagick {}
	public function despeckleimage(): Gmagick {}
	public function destroy(): bool {}
	public function drawimage(GmagickDraw $drawing_wand): Gmagick {}
	public function edgeimage(float $radius): Gmagick {}
	public function embossimage(float $radius, float $sigma): Gmagick {}
	public function enhanceimage(): Gmagick {}
	public function equalizeimage(): Gmagick {}
	public function flipimage(): Gmagick {}
	public function flopimage(): Gmagick {}
	public function frameimage(GmagickPixel|string $color, int $width, int $height, int $inner_bevel, int $outer_bevel): Gmagick {}
	public function gammaimage(float $gamma): Gmagick {}
	public function getcopyright(): string {}
	public function getfilename(): string {}
	public function getimage(): Gmagick {}
	public function setimage(Gmagick $replace): bool {}
	public function getimagebackgroundcolor(): GmagickPixel {}
	public function getimageblob(): string {}
	public function getimagesblob(): string {}
	public function getimageblueprimary(): array {}
	public function getimagebordercolor(): GmagickPixel {}
	public function getimagechanneldepth(int $channel_type): int {}
	public function getimagecolors(): int {}
	public function getimagecolorspace(): int {}
	public function getimagecompose(): int {}
	public function getimagedelay(): int {}
	public function getimagedepth(): int {}
	public function getnumberimages(): int {}
	public function getimagedispose(): int {}
	public function getimageextrema(): array {}
	public function getimagefilename(): string {}
	public function getimagegamma(): float {}
	public function getimagegreenprimary(): array {}
	public function getimageheight(): int {}
	public function getimagehistogram(): array {}
	public function getimageindex(): int {}
	public function getimageinterlacescheme(): int {}
	public function getimageiterations(): int {}
	public function getimagemattecolor(): GmagickPixel {}
	public function getimageprofile(string $name): string {}
	public function getimageredprimary(): array {}
	public function getimagerenderingintent(): int {}
	public function getimageresolution(): array {}
	public function getimagescene(): int {}
	public function getimagesignature(): string {}
	public function getimagetype(): int {}
	public function getimageunits(): int {}
	public function getimagewhitepoint(): array {}
	public function getimagewidth(): int {}
	public function getpackagename(): string {}
	public function getquantumdepth(): array {}
	public function getreleasedate(): string {}
	public function getsamplingfactors(): array {}
	public function getsize(): array {}
	public function setinterlacescheme(int $interlace_scheme): Gmagick {}
	public function hasnextimage(): Gmagick {}
	public function haspreviousimage(): Gmagick {}
	public function implodeimage(float $radius): Gmagick {}
	public function labelimage(string $label): Gmagick {}
	public function levelimage(float $blackPoint, float $gamma, float $whitePoint, int $channel = Gmagick::CHANNEL_DEFAULT): Gmagick {}
	public function magnifyimage(): Gmagick {}
	public function mapimage(gmagick $gmagick, bool $dither): Gmagick {}
	public function medianfilterimage(float $radius): void {}
	public function minifyimage(): Gmagick {}
	public function modulateimage(float $brightness, float $saturation, float $hue): Gmagick {}
	public function motionblurimage(float $radius, float $sigma, float $angle): Gmagick {}
	public function newimage(int $width, int $height, string $background, ?string $format = null): Gmagick {}
	public function nextimage(): bool {}
	public function normalizeimage(): Gmagick {}
	public function oilpaintimage(float $radius): Gmagick {}
	public function previousimage(): bool {}
	public function profileimage(string $name, string $profile): Gmagick {}
	public function quantizeimage(int $numColors, int $colorspace, int $treeDepth, bool $dither, bool $measureError): Gmagick {}
	public function quantizeimages(int $numColors, int $colorspace, int $treeDepth, bool $dither, bool $measureError): Gmagick {}
	public function queryfontmetrics(GmagickDraw $draw, string $text): array {}
	public function queryfonts(string $pattern = "*"): array {}
	public function queryformats(string $pattern = "*"): array {}
	public function radialblurimage(float $angle, int $channel = Gmagick::CHANNEL_DEFAULT): Gmagick {}
	public function raiseimage(int $width, int $height, int $x, int $y, bool $raise): Gmagick {}
	public function readimageblob(string $imageContents, ?string $filename = null): Gmagick {}
	public function reducenoiseimage(float $radius): Gmagick {}
	public function removeimage(): Gmagick {}
	public function removeimageprofile(string $name): string {}
	public function resampleimage(float $xResolution, float $yResolution, int $filter, float $blur): Gmagick {}
	public function rollimage(int $x, int $y): Gmagick {}
	public function rotateimage(GmagickPixel|string $background, float $degrees): Gmagick {}
	public function scaleimage(int $width, int $height, bool $fit = false): Gmagick {}
	public function separateimagechannel(int $channel): Gmagick {}
	public function setfilename(string $filename): Gmagick {}
	public function setimagebackgroundcolor(GmagickPixel|string $color): Gmagick {}
	public function setimageblueprimary(float $x, float $y): Gmagick {}
	public function setimagebordercolor(GmagickPixel|string $color): Gmagick {}
	public function setimagechanneldepth(int $channel, int $depth): Gmagick {}
	public function setimagecolorspace(int $colorspace): Gmagick {}
	public function setimagecompose(int $composite): Gmagick {}
	public function getimagecompression(): int {}
	public function setimagecompression(int $compression): Gmagick {}
	public function setimagedelay(int $delay): Gmagick {}
	public function setimagedepth(int $depth): Gmagick {}
	public function setimagedispose(int $disposeType): Gmagick {}
	public function setimagefilename(string $filename): Gmagick {}
	public function getimageformat(): string {}
	public function setimageformat(string $imageFormat): Gmagick {}
	public function setimagegamma(float $gamma): Gmagick {}
	public function setimagegreenprimary(float $x, float $y): Gmagick {}
	public function setimageindex(int $index): Gmagick {}
	public function setimageinterlacescheme(int $interlace): Gmagick {}
	public function setimageiterations(int $iterations): Gmagick {}
	public function setimageprofile(string $name, string $profile): Gmagick {}
	public function setimageredprimary(float $x, float $y): Gmagick {}
	public function setimagerenderingintent(int $rendering_intent): Gmagick {}
	public function setimageresolution(float $xResolution, float $yResolution): Gmagick {}
	public function setimagescene(int $scene): Gmagick {}
	public function setimagetype(int $imgType): Gmagick {}
	public function setimageunits(int $resolution): Gmagick {}
	public function setimagewhitepoint(float $x, float $y): Gmagick {}
	public function setsamplingfactors(array $factors): Gmagick {}
	public function setsize(int $columns, int $rows): Gmagick {}
	public function shearimage(GmagickPixel|string $background, float $xShear, float $yShear): Gmagick {}
	public function solarizeimage(int $threshold): Gmagick {}
	public function spreadimage(float $radius): Gmagick {}
	public function stripimage(): Gmagick {}
	public function swirlimage(float $degrees): Gmagick {}
	public function trimimage(float $fuzz): Gmagick {}
	public function blackthresholdimage(GmagickPixel|string $threshold): bool {}
	public function whitethresholdimage(GmagickPixel|string $threshold): bool {}
	public function colordecisionlist(string $color_correction_collection): bool {}
	public function clipimage(): bool {}
	public function clippathimage(string $pathname, bool $inside): bool {}
	/**
	 * @param GmagickPixel|string $fill
	 * @param float $fuzz
	 * @param GmagickPixel|string $bordercolor
	 * @param int $x
	 * @param int $y
	 */
	public function colorfloodfillimage($fill, float $fuzz, GmagickPixel|string $bordercolor, int $x, int $y): bool {}
	/** @param GmagickPixel|string $colorize */
	public function colorizeimage($colorize, GmagickPixel|string $opacity): bool {}
	public function compareimagechannels(Gmagick $reference, int $channel, int $metric): array {}
	public function compareimages(Gmagick $reference, int $metric): array {}
	public function contrastimage(bool $sharpen): bool {}
	public function convolveimage(array $kernel): bool {}
	public function extentimage(int $width, int $height, int $x, int $y): bool {}
	public function getimageboundingbox(float $fuzz): array {}
	public function getimageattribute(string $key): string {}
	public function setimageattribute(string $key, string $attribute): bool {}
	public function getimagechannelextrema(int $channel): array {}
	public function getimagechannelmean(int $channel): array {}
	public function getimagecolormapcolor(int $index): GmagickPixel {}
	/**
	 * @param int $index
	 * @param GmagickPixel|string $color
	 **/
	public function setimagecolormapcolor(int $index, $color): bool {}
	public function getimagegravity(): int {}
#ifdef HAVE_GMAGICK_SET_IMAGE_GRAVITY
	public function setimagegravity(int $gravity): bool {}
#endif
	/** @param GmagickPixel|string $color */
	public function setimagemattecolor($color): bool {}
	public function getimagevirtualpixelmethod(): int {}
	public function setimagevirtualpixelmethod(int $method): bool {}
	public function haldclutimage(Gmagick $hald): bool {}
	/**
	 * @param float $alpha
	 * @param float $fuzz
	 * @param GmagickPixel|string $bordercolor
	 * @param int $x
	 * @param int $y
	 */
	public function mattefloodfillimage(float $alpha, float $fuzz, $bordercolor, int $x, int $y): bool {}
	public function montageimage(GmagickDraw $drawing_wand, string $tile_geometry, string $thumbnail_geometry, int $mode, string $frame): Gmagick {}
	public function morphimages(int $frames): Gmagick {}
	public function mosaicimages(): Gmagick {}
	public function shaveimage(int $columns, int $rows): bool {}
	public function steganoimage(Gmagick $watermark_wand, int $offset): Gmagick {}
	public function stereoimage(Gmagick $object_wand): Gmagick {}
	public function transformimage(string $crop, string $geometry): Gmagick {}
	public function waveimage(float $amplitude, float $length): bool {}
	public function getimagefuzz(): float {}
	public function setimagefuzz(float $fuzz): Gmagick {}
	public function getimagesavedtype(): int {}
	public function setdepth(int $depth): Gmagick {}
	public function setimageoption(string $format, string $key, string $value): bool {}
	public function setimagesavedtype(int $type): bool {}
	public function setformat(string $format): bool {}
	public function setresolutionunits(int $resolution_type): bool {}
	public function getimagegeometry(): array {}
	public function getresourcelimit(int $type): int {}
	public function setresourcelimit(int $type, int $limit): bool {}
	public function negateimage(bool $gray, int $channel = Gmagick::CHANNEL_DEFAULT): bool {}
	public function sharpenimage(float $radius, float $sigma): bool {}
	public function textureimage(Gmagick $texture_wand): Gmagick {}
	public function flattenimages(): Gmagick {}
	public function sampleimage(int $cols, int $rows, bool $fit = false, bool $legacy = false): Gmagick {}
	public function cloneimage(): Gmagick {}
	public function appendimages(): Gmagick {}
	public function unsharpmaskimage(float $radius, float $sigma, float $amount, float $threshold): Gmagick {}
	public function setresolution(float $x_resolution, float $y_resolution, float $amount, float $threshold): bool {}
	public function adaptivethresholdimage(int $width, int $height, int $offset): bool {}
	public function affinetransformimage(GmagickDraw $drawing_wand): bool {}
	public function averageimages(): Gmagick {}
}

class GmagickPixel {
	public function __construct(?string $color = null) {}
	public function getcolor(bool $as_array = false, bool $normalize_array = false): string|array {}
	public function setcolor(string $color): GmagickPixel {}
	public function getcolorcount(): int {}
	public function setcolorcount(int $color_count): GmagickPixel {}
	public function getcolorvalue(int $color): float {}
	public function setcolorvalue(int $color, float $value): GmagickPixel {}
	public function getcolorvaluequantum(int $color): int {}
	public function setcolorvaluequantum(int $color, float $value): GmagickPixel {}
}

class GmagickDraw {
	public function setstrokecolor(GmagickPixel|string $color): GmagickDraw {}
	public function setstrokewidth(float $width): GmagickDraw {}
	public function ellipse(float $ox, float $oy, float $rx, float $ry, float $start, float $end): GmagickDraw {}
	public function annotate(float $x, float $y, string $text): GmagickDraw {}
	public function affine(array $affine): bool {}
	public function arc(float $sx, float $sy, float $ex, float $ey, float $sd, float $ed): GmagickDraw {}
	public function bezier(array $coordinates): GmagickDraw {}
	public function getfillcolor(): GmagickPixel {}
	public function getfillopacity(): float {}
	public function getfont(): string|false {}
	public function getfontfamily(): string|false {}
	public function setfontfamily(string $font_family): GmagickDraw {}
	public function getfontsize(): float {}
	public function getfontstyle(): int {}
	public function getfontweight(): int {}
	public function getstrokeopacity(): float {}
	public function getstrokecolor(): GmagickPixel {}
	public function getstrokewidth(): float {}
	public function gettextdecoration(): int {}
	public function gettextencoding(): string|false {}
	public function line(float $sx, float $sy, float $ex, float $ey): GmagickDraw {}
	public function point(float $x, float $y): GmagickDraw {}
	public function polygon(array $coordinates): GmagickDraw {}
	public function polyline(array $coordinates): GmagickDraw {}
	public function rectangle(float $x1, float $y1, float $x2, float $y2): GmagickDraw {}
	public function rotate(float $degrees): GmagickDraw {}
	public function roundrectangle(float $x1, float $y1, float $x2, float $y2, float $rx, float $ry): GmagickDraw {}
	public function scale(float $x, float $y): GmagickDraw {}
	public function setfillcolor(GmagickPixel|string $color): GmagickDraw {}
	public function setfillopacity(float $fill_opacity): GmagickDraw {}
	public function setfont(string $font): GmagickDraw {}
	public function setfontsize(float $pointsize): GmagickDraw {}
	public function setfontstyle(int $style): GmagickDraw {}
	public function setfontweight(int $weight): GmagickDraw {}
	public function setstrokeopacity(float $stroke_opacity): GmagickDraw {}
	public function settextdecoration(int $decoration): GmagickDraw {}
	public function settextencoding(string $encoding): GmagickDraw {}
	public function getgravity(): int {}
	public function setgravity(int $gravity): GmagickDraw {}
	public function getstrokeantialias(): bool {}
	public function setstrokeantialias(bool $antialias): GmagickDraw {}
	public function getstrokedashoffset(): float {}
	public function setstrokedashoffset(float $offset): GmagickDraw {}
	public function getstrokelinecap(): int {}
	public function setstrokelinecap(int $linecap): GmagickDraw {}
	public function getstrokelinejoin(): int {}
	public function setstrokelinejoin(int $linejoin): GmagickDraw {}
	public function getstrokemiterlimit(): int {}
	public function setstrokemiterlimit(int $miterlimit): GmagickDraw {}
#if GMAGICK_LIB_MASK >= 1003000
	public function getstrokedasharray(): array {}
	public function setstrokedasharray(array $dash_array): GmagickDraw {}
#endif
	public function circle(float $ox, float $oy, float $px, float $py): GmagickDraw {}
	public function getclippath(): string|false {}
	public function setclippath(string $clip_mask): GmagickDraw {}
	public function getcliprule(): int {}
	public function setcliprule(int $fill_rule): GmagickDraw {}
	public function getclipunits(): int {}
	public function setclipunits(int $clip_units): GmagickDraw {}
	public function color(float $x, float $y, int $paint_method): GmagickDraw {}
	public function comment(string $comment): GmagickDraw {}
	public function setfillpatternurl(string $fill_url): GmagickDraw {}
	public function getfillrule(): int {}
	public function setfillrule(string $fill_rule): GmagickDraw {}
	public function getfontstretch(): int {}
	public function setfontstretch(int $font_stretch): bool {}
	public function pathclose(): GmagickDraw {}
	public function pathcurvetoabsolute(float $x1, float $y1, float $x2, float $y2, float $x, float $y): GmagickDraw {}
	public function pathcurvetorelative(float $x1, float $y1, float $x2, float $y2, float $x, float $y): GmagickDraw {}
	public function pathcurvetoquadraticbezierabsolute(float $x1, float $y1, float $x, float $y): GmagickDraw {}
	public function pathcurvetoquadraticbezierrelative(float $x1, float $y1, float $x, float $y): GmagickDraw {}
	public function pathcurvetoquadraticbeziersmoothabsolute(float $x, float $y): GmagickDraw {}
	public function pathcurvetoquadraticbeziersmoothrelative(float $x, float $y): GmagickDraw {}
	public function pathcurvetosmoothabsolute(float $x1, float $y1, float $x, float $y): GmagickDraw {}
	public function pathcurvetosmoothrelative(float $x1, float $y1, float $x, float $y): GmagickDraw {}
	public function pathellipticarcabsolute(float $rx, float $ry, float $x_axis_rotation, bool $large_arc_flag, bool $sweep_flag, float $x, float $y): GmagickDraw {}
	public function pathellipticarcrelative(float $rx, float $ry, float $x_axis_rotation, bool $large_arc_flag, bool $sweep_flag, float $x, float $y): GmagickDraw {}
	public function pathmovetoabsolute(float $x, float $y): GmagickDraw {}
	public function pathmovetorelative(float $x, float $y): GmagickDraw {}
	public function pathlinetoabsolute(float $x, float $y): GmagickDraw {}
	public function pathlinetorelative(float $x, float $y): GmagickDraw {}
	public function pathlinetohorizontalabsolute(float $x): GmagickDraw {}
	public function pathlinetohorizontalrelative(float $x): GmagickDraw {}
	public function pathlinetoverticalabsolute(float $y): GmagickDraw {}
	public function pathlinetoverticalrelative(float $y): GmagickDraw {}
	public function pathstart(): GmagickDraw {}
	public function pathfinish(): GmagickDraw {}
	public function popclippath(): GmagickDraw {}
	public function popdefs(): GmagickDraw {}
	public function pushdefs(): GmagickDraw {}
	public function poppattern(): GmagickDraw {}
	public function pushpattern(string $pattern_id, float $x, float $y, float $width, float $height): GmagickDraw {}
	public function pushclippath(string $clip_mask_id): GmagickDraw {}
	public function skewx(float $degrees): GmagickDraw {}
	public function skewy(float $degrees): GmagickDraw {}
	public function setstrokepatternurl(string $stroke_url): GmagickDraw {}
	public function gettextantialias(): bool {}
	public function settextantialias(bool $anti_alias): bool {}
	public function gettextundercolor(): GmagickPixel {}
	public function settextundercolor(GmagickPixel|string $color): GmagickDraw {}
	public function translate(float $x, float $y): GmagickDraw {}
	public function setviewbox(float $x1, float $y1, float $x2, float $y2): GmagickDraw {}
	public function popGraphicContext(): GmagickDraw {}
	public function pushGraphicContext(): GmagickDraw {}
}

