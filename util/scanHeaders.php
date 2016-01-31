<?php

// A simple tool to scan for missed enum entries in the GraphicsMagick header files.
// 
// It works by extracting all the values for the enums listed from the header files
// and checking that they are defined in gmagick_helpers.c

$directory = false;
// Either pass in the directory to scan or set it here.
$directory = "../../GM";

if ($directory) {
	$pathToImageMagick = $directory;
}
else {
	if ($argc != 2) {
		echo "usage 'php scanHeaders.php /path/to/GraphicsMagick\n";
		exit(-1);
	}

	$pathToImageMagick = $argv[1];
}

$pathToImageMagick .= '/';

if (file_exists($pathToImageMagick) == false || 
	is_dir($pathToImageMagick) == false) {
	echo "Path $pathToImageMagick is not accessible.\n";
	exit(-1);
}


$enumToCheck = [
	'magick/colorspace.h' => [
		'ColorspaceType',
	],
	'magick/compare.h' => [
		//'HighlightStyle', // not exposed currently  
		'MetricType',
	],
	'magick/constitute.h' => [
		// 'QuantumType', // not exposed currently
		// 'QuantumSampleType', // not exposed currently
		'StorageType',
	],
	'magick/image.h' => [
		// 'AlphaType',    // not exposed currently
		'ChannelType',
		// 'ClassType',    // not exposed currently
		'CompositeOperator',
		'CompressionType',
		'DisposeType',
		// 'EndianType', // not exposed currently
		'FilterTypes',
		//'GeometryFlags', // not exposed currently
		// 'GravityType', // not exposed currently
		'ImageType',
		'InterlaceType',
		'MontageMode',
		'NoiseType',
		'OrientationType',
		'PreviewType',
		'RenderingIntent',
		'ResolutionType',
	],
	'magick/operator.h' => [
		//'QuantumOperator', // not exposed currently
	],

	'magick/pixel_cache.h' => [
		'VirtualPixelMethod',
	],

	'magick/render.h' => [
		'AlignType',
		'ClipPathUnits',
		'DecorationType',
		'FillRule',
		// 'GradientType',   // not exposed currently
		'LineCap',
		'LineJoin',
		'PaintMethod',
		//'PrimitiveType',    // not exposed currently
		// 'ReferenceType', // not exposed currently 
		// 'SpreadMethod'  // not exposed currently
	],

	'magick/resource.h' => [
		'ResourceType'
	],

	'magick/type.h' => [
		'StretchType',
		'StyleType',
	],

];

$gmagickHelperContents = file_get_contents("../gmagick_helpers.c");

if ($gmagickHelperContents == false) {
	echo "failed to read ../gmagick_helpers.c\n";
	exit(-1);
}

// We don't use these enums currently.
$skipEnumList = [
//	'ComplexOperator', // used by ComplexImages - not exposed in wand api
//	'PixelComponent', // present in 6.9.2 but not used?
//	'PixelIntensityMethod', // Used by GrayscaleImage function that is not expose in wand api
];


foreach ($enumToCheck as $filename => $enums) {
	foreach ($enums as $enum) {
		if (in_array($enum, $skipEnumList)) {
			//We don't use these enums currently.
			continue;
		}

		$enumNameList = getEnumList($enum, $pathToImageMagick.$filename);
		foreach ($enumNameList as $enumName) {
			//echo "checking for $enumName\n";
			if (stripos($gmagickHelperContents, $enumName) === false) {
				echo "value '$enumName' is missing for enum $enum.\n";
			}
		}
	}
}





function getEnumList($enum, $filename)
{
	$fileContents = file_get_contents($filename);

	if ($fileContents === false) {
		echo "Could not read file $filename \n";
		exit(-1);
	}

	// These characters mess with the matching.
	$searchReplace = [
		','
	];

	$pregString = "#\{([^\{\}]*)\}\s*$enum#sU";

	preg_match($pregString, $fileContents, $matches);

	if (count($matches) == 0) {
		echo "Couldn't find enum $enum in $filename.\n";
		return [];
	}

	$match = $matches[1];

	foreach ($searchReplace as $search) {
		$match = str_replace($search, '', $match);
	}

	$match = preg_replace("#/\*.*\*/#sU", '', $match);

	$vars = explode("\n", $match);

	$trimmedVars = [];

	foreach ($vars as $var) {
		if (stripos($var, 'Undefined') !== false) {
			continue;
		}

		if (stripos($var, '#undef') !== false) {
			continue;
		}
		
		$equalsPosition = strpos($var, '=');
		if ($equalsPosition !== false) {
			$var = substr($var, 0, $equalsPosition);
		}

		$entry = trim($var);

		if (strlen($entry) === 0) {
			continue;
		}
		$trimmedVars[] = $entry;
	}

	return $trimmedVars;
}
