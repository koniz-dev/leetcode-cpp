<?php
function isValid($s) {
    $stack = array();
    $map = array(")" => "(", "}" => "{", "]" => "[");
    for ($i = 0; $i < strlen($s); $i++) {
        $c = $s[$i];
        if (in_array($c, $map)) {
            array_push($stack, $c);
        } elseif (array_key_exists($c, $map)) {
            if (empty($stack) || array_pop($stack) != $map[$c]) {
                return false;
            }
        }
    }
    return empty($stack);
}
?>
