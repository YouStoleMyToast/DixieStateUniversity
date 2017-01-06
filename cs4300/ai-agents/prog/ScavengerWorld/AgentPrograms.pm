#
#
#
our $aps =
[
{
name => 'Snorlax',
key  => 'S',
header => 'Snorlax.h',
cpp    => ['Snorlax.cpp'],
constructor => 'ai::Sample::Snorlax(opts)',
},
{
name => 'Manual',
key  => 'm',
header => 'Manual.h',
cpp    => ['Manual.cpp'],
constructor => 'ai::Sample::Manual()',
},
{
name => 'pikachu',
key  => 'p',
header => 'eebpikachu.h',
cpp    => ['eebpikachu.cpp'],
constructor => 'eebp::pikachu(opts)',
},
{
name => 'Gyarados',
key  => 'y',
header => 'eebgyarados.h',
cpp    => ['eebgyarados.cpp','eebymodel.cpp','eebyproblem.cpp','eebystate.cpp','eebyaction.cpp'],
constructor => 'eeby::Gyarados(opts)',
},
{
name => 'Glados',
key  => 'g',
header => 'eebglados.h',
cpp    => ['eebglados.cpp','eebmodel.cpp','eebproblem.cpp','eebstate.cpp','eebaction.cpp'],
constructor => 'eeb::Glados(opts)',
},
#{
#  name => '',
#  key  => '',
#  header => '',
#  constructor => '',
#},
 ];

1;
