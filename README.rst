PHP Snowball Stemmer extension
==============================

This PHP extension wraps the C-language version of the stemmers provided by the
snowball project. http://snowballstem.org/

Usage:

.. code-block:: php
   
   <?php
   $s = stemmer_create("spanish");
   echo stemmer_apply($s, "bailando");
   // Output: bail


Alternatives:

- https://pecl.php.net/package/stem/%20PECL%20extension%20to%20the%20Snowball%20API%20for%20PHP
- https://github.com/hthetiot/php-stemmer
