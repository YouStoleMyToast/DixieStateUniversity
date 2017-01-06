#
#
#
our $aps =
[
 {
   name => 'Artemis',
   key  => 'a',
   header => 'eebartemis.h',
   cpp    => ['eebartemis.cpp'],
   constructor => 'eeba::Artemis()',
 },
 {
   name => 'Birgitte',
   key  => 'b',
   header => 'eebbirgitte.h',
   cpp    => ['eebbirgitte.cpp'],
   constructor => 'eebb::Birgitte()',
 },
 {
   name => 'Trimaxion',
   key  => 't',
   header => 'eebtrimaxion.h',
   cpp    => ['eebtrimaxion.cpp'],
   constructor => 'eebt::Trimaxion()',
 },
 {
   name => 'Simpleton',
   key  => 'S',
   header => 'Simpleton.h',
   cpp    => ['Simpleton.cpp'],
   constructor => 'ai::Sample::Simpleton()',
 },
 {
   name => 'Aristotle',
   key  => 'A',
   header => 'Aristotle.h',
   cpp    => ['Aristotle.cpp'],
   constructor => 'ai::Sample::Aristotle()',
 },
#{
#  name => '',
#  key  => '',
#  header => '',
#  constructor => '',
#},
 ];

1;
