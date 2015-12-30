<?php

if (!extension_loaded("gmagick")) die("skip");

function checkClassMethods($class, $methods)
{
	foreach ($methods as $method) {
		if (method_exists($class, $method) == false) {
			die("skip Class method $class::$method not present");
		}
	}
}
