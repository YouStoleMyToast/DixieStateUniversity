   M S B A M L   `   `   `  ����J  FSudokuFX, Version=1.0.5388.31462, Culture=neutral, PublicKeyToken=null#clr-namespace:SudokuFXSudokuFX  5          SudokuFX.GraphControl   5   
   \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      $clrclr-namespace:SudokuFX    5      
����������	#60FFFFFF$��Stretch=�5      $��Bottom=�5      $��Disabled=�5	        � 	Resources  5         BarTemplate �Name �� Path
 � Tag  BarColorConverter �� 	Converter �� RadiusX �� RadiusY J� BitmapEffect F� Opacity	 �� Color
 �� ElementName  ColorLightnessConverter �� ConverterParameter � SpreadMethod � MappingMode �� 
StartPoint �� EndPoint �� 	Transform �� ScaleX �� ScaleY � Offset � Color ��Name � LayoutTransform �� Angle �� Triggers �� Value �� Binding �� 
TargetName �� Property �� Value    SudokuFX.BarColorConverter&    SudokuFX.ColorLightnessConverter��%�  &	        7  7  7  7  &	 O    &	 b    �� 5      .R�5      � $	 Bar��6   $��3,3,3,0q�6   $��50��6+   $��Bottom=�67   ��6R   �� $ 	BarHeight� 6t   �� $ Index�8   .+�5   
   �� $ 3��6   $ 3��6!   
������ $��2��6C   $��Stretch=�6W   $��Stretch=�6t   
���   � 5      F� 5      $	 0.5Q�6%   5      �� 5   
   $ 3��6   $ 3��6!   $��2��6/   $��Stretch=�6C   $��Stretch=�6`   ��5      �� 5      	 6   �� $	
 Bar��$	 Tag�8  $	 -64����5      �� 5      $ Repeat=�6"   $ Absolute=�68   $	 0,0&�6O   $	 1,1&�6`    5      �� 5      $ 20Q�6!   $ 20Q�6-   .��5      � $ 0Q�6�    6   �� $	
 Bar��$	 Tag�8  $	 -32��6�   � 5      $ 0.499Q�6�    6   �� $	
 Bar��$	 Tag�8  $	 -32��6�   � 5      $ 0.501Q�6I    6   �� $	
 Bar��$	 Tag�6I   � 5      $ 1Q�6I    6   �� $	
 Bar��$	 Tag�6I   5       5"      �� 5#   
   $ 3��6   $ 3��6!   $��2q�6-   $��Stretch=�69   $��Stretch=�6V   ��5$      �� 5%      $	 0,0&�6"   $	 1,0&�63   .��5&      � $ 	#10FFFFFF��6   $ 0Q�6/   � 5'      $ 	#50FFFFFF��6   $	 0.3Q�6/   � 5(      $ 	#60FFFFFF��6   $	 0.5Q�6/   � 5)      $ 	#50FFFFFF��6   $	 0.7Q�6/   � 5*      $ 	#00FFFFFF��6   $ 1Q�6/   5+      5-      �� 5.   
   $ 3��6   $ 3��6!   $	��3.5q�6-   $��Stretch=�6<   $��Stretch=�6Y   ��5/      �� 50      $	 0,0&�6"   $	 0,1&�63   .��51      � $ 	#80FFFFFF��6   $ 0Q�6/   � 52      $ 	#00FFFFFF��6   $	 0.4Q�6/   � 53      $ 	#00FFFFFF��6   $
 0.85Q�6/   � 54      $ 	#40FFFFFF��6   $ 1Q�6/   55      57      �� 58   
   $ BarText��6   $��Center=�6%   
�������$��Center=�6T   ��6q   �� $ 	TimeTaken� 59      �� 5:      $ 90Q�6   5<      5=   	    5>      �� 5?   
   $
 True��66    6   �� $ Failed�.a�5@      �� $	 Bar��6    �@J�Opacity$	 0.5Q�67   �� 5A      $ BarText��6    � ��$ Failed��68   5B      5D        5E      6     5F      6"   5G      ��5H      �� 5I       �� 
TargetType" ��6   .�5J      ��  � ��$ Bottom=�63    �� Triggers 5K      P� 5L   
     P� Property  �@J�	IsVisible! P� Value! . " N� EnterActions" 5M      �� 5N      .��5O      �� .��5P      W� # W� From$# 0X�6"   	$ W� To$$ 1X�6+   % �� TargetProperty$% Opacity�63   & g� Duration$& 0:0:0.5D�6W   5Q      5R      5T      5V      ��5X      �� 5Y      .R�5Z      �� $��Stretch=�6   ' �� Orientation$' 
Horizontal=�6/   5[      ��5]      �� 5^      ( �� ResourceKey$( BarTemplate��6   5`      