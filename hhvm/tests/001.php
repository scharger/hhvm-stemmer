<?hh // partial

echo "Check:\n";
echo "\thh_stem function exists: ";
if (function_exists("hh_stem")) {
	echo "yes\n";
	echo "\t\tcheck hh_stem function (expect: bail): ";
	echo hh_stem("spanish", "bailando");
	echo "\n";
} else {
		echo "no\n";
}