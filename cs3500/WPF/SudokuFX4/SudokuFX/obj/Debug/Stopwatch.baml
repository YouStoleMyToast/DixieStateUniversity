   M S B A M L   `   `   `  ����J  FSudokuFX, Version=1.0.5388.30936, Culture=neutral, PublicKeyToken=null#clr-namespace:SudokuFXSudokuFX  5          SudokuFX.Stopwatch   5      \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      $clrclr-namespace:SudokuFX    5      ��5      ��   �� RelativeSource  �� *Self+ �� Path$ ActualWidth� � 	Resources 5         SudokuFX.AngleConverter   AngleConverter��%   &	          5      6   5      ��5	      �� 5
       �� 
TargetType" d�6   .R�5      �  �Name$ MainGrid��6   .+�5   
   ��  ��Name$ OnLight��6   $y�Hidden=�6&   $��Stretch=�6:   $��Stretch=�6Y    J� BitmapEffect 5      O� 5       O� GlowSize$ 10Q�6$    O� 	GlowColor$ 	LimeGreen��62   ��5      L� 5      	 j� Stretch$	 Uniform=�6   
 L� Drawing
 5      I� 5      .��5      �  � Geometry 5      �� 5       �� Rect$ 0,0,1,1�6*   5      � 5       � Brush
 �/���
 � Pen 5      >� 5       >� Brush
 �2�2� >� 	Thickness$
 0.02Q�6/    5      �� 5       �� RadiusX$
 0.05Q�6*    �� RadiusY$
 0.05Q�6:   $ 0.375,0,0.25,0.33�6J   5       � 5!       5"      �� 5#       �� 
StartPoint$	 0,0&�6,    �� EndPoint$	 1,1&�6=   .��5$      �  � Color$ 	#A0FFFFFF��6'    � Offset$ 0Q�6:   � 5%      $ 	#00FFFFFF��6'   $ 1Q�6:   5&       5(      �� 5)      $
 0.05Q�6*   $
 0.05Q�6:   $ 0.4,0.025,0.2,0.075�6J   5+      5,      5.      50      �� 51   
   $ OffLight��6   $��Stretch=�6'   $��Stretch=�6F   ��52      L� 53      $	 Uniform=�6   
 54      I� 55      .��56      �  57      �� 58      $ 0,0,1,1�6*   5:      � 5;      
 � � � 5<      >� 5=      
 � d �$
 0.02Q�6/    5?      �� 5@      $
 0.05Q�6*   $
 0.05Q�6:   $ 0.375,0,0.25,0.33�6J   5B      � 5C       5D      �� 5E      $	 0,0&�6,   $	 1,1&�6=   .��5F      � $ 	#A0FFFFFF��6'   $ 0Q�6:   � 5G      $ 	#00FFFFFF��6'   $ 1Q�6:   5H       5J      �� 5K      $
 0.05Q�6*   $
 0.05Q�6:   $ 0.4,0.025,0.2,0.075�6J   5M      5N      5P      5R      �� 5S   
   $ Watch��6   $��10q�6$   $��Stretch=�61   $��Stretch=�6P   ��5T      L� 5U      $	 Uniform=�6   
 5V      I� 5W      .��5Y      �  5Z      �� 5[      $	 0,0&�6,   $	 1,1&�6>   .��5\      � $ 	#FF7C888E��6'   $ 0Q�69   � 5]      $ 	#FFbDc3cC��6'   $ 0.229492Q�69   � 5^      $ 	#FF94a0a5��6'   $ 0.364258Q�69   � 5_      $ 	#FFd8dEe1��6'   $ 0.584961Q�69   � 5`      $ 	#FFa8aEbA��6'   $ 0.699219Q�69   � 5a      $ 	#FFcCcFd5��6'   $ 0.78418Q�69   � 5b      $ 	#FFa2a8aE��6'   $ 0.879883Q�69   � 5c      $ 	#FFd8dEe7��6'   $ 1Q�69   5d       5f      >� 5g      $ 2Q�6    5h      �� 5i      $	 0,0&�60   $	 1,1&�6B   .��5j      � $ 	#FFcCcFd5��6+   $ 0Q�6>   � 5k      $ 	#FF7C888E��6+   $ 1Q�6>   5l      5n       5p      �� 5q       �� GeometryCombineMode$ Union=�6)    �� 	Geometry1 5r      @� 5s       @� Center$ 50,66&�6,    @� RadiusX$ 40Q�6<    @� RadiusY$ 40Q�6J    �� 	Geometry2 5u      �� 5v      $ Union=�6-    5w      �� 5x       $ 5Q�62   $ 5Q�6?   $ 37.5,20,25,33�6L    � 	Transform 5y   "   �� 5z   $    �� CenterX$ 50Q�64    �� CenterY$ 66Q�6B     �� Angle$  45Q�6P   5|   !    5~      �� 5       $ 5Q�62   $ 5Q�6?   $ 37.5,20,25,33�6L    5�   "   �� 5�   $   $ 50Q�64   $ 66Q�6B   $	  -45Q�6P   5�   !   5�      5�      5�      � 5�       5�      >� 5�      $ 2Q�6    5�      �� 5�      $	 1,1&�60   $	 0,0&�6B   .��5�      � $ 	#FFcCcFd5��6+   $ 0Q�6>   � 5�      $ 	#FF7C888E��6+   $ 1Q�6>   5�      5�       5�      �� 5�      ! �� Opacity$! 1Q�6,   $	 0,0&�68   $	 1,1&�6J   .��5�      � $ 	Gainsboro��6'   $ 0Q�6;   � 5�      $ 	LightGray��6'   $ 1Q�6:   5�       5�      @� 5�      $ 50,66&�6(   $ 30Q�68   $ 30Q�6F   5�      � 5�       5�      >� 5�      
 �����$	 1.5Q�6*    5�      � 5�      .��5�      �� " �� 
StartPoint$" 50,43&�6'   # �� EndPoint$# 50,51&�6;   �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $  30Q�6J   5�      �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $  60Q�6J   5�      �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $  90Q�6J   5�      �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $	  120Q�6J   5�      �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $	  150Q�6J   5�      �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $	  180Q�6J   5�      �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $	  -30Q�6J   5�      �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $	  -60Q�6J   5�      �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $	  -90Q�6J   5�      �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $
  -120Q�6J   5�      �� 5�      $" 50,43&�6'   $# 50,47&�6;    5�      �� 5�      $ 50Q�6.   $ 66Q�6<   $
  -150Q�6J   5�      5�      5�      � 5�       �	#50000000 5�      B� 5�      .��5�      E� $ E� IsClosed$ . % E� IsFilled% . & E� 
StartPoint$& 50,40&�6G   .��5�      �� ' �� Point$' 51,66&�6(   �� 5�      $' 49,66&�6(   5�       5�      V� 5�      .~�5�      �� $ 50Q�6.   $ 66Q�6<     6J   �� $ CurrentTime�  �� *TemplatedParent+( �� 	Converter#( [  T� 5�      ) T� Y$) 1Q�61   5�      5�      5�      � 5�      
 �  �� 5�      B� 5�      .��5�      E� $ . % . $& 50,40&�6G   .��5�      �� $' 51,66&�6(   �� 5�      $' 49,66&�6(   5�       5�      �� 5�      $ 50Q�6,   $ 66Q�6:     6H   �� $ CurrentTime�  �� *TemplatedParent+#( [  5�      5      � 5      5     >� 5     $ 5Q�6   
 ���� 6+    5     
� 5     * 
� RadiusX$
* 1.25Q�6,   + 
� RadiusY$+ 1Q�6<   , 
� Center$, 0.5,0&�6H   - 
� GradientOrigin$- 0.5,0&�6W   .��5     � $ 	#FFFFFFFF��6'   $ 0Q�69   � 5	     $ 	#40FFFFFF��6'   $
 0.55Q�69   � 5
     $ 	#00FFFFFF��6'   $
 0.56Q�69   � 5     $ 	#00FFFFFF��6'   $
 0.75Q�69   � 5     $ 	#FFFFFFFF��6'   $ 1Q�69   5      5     @� 5     $ 50,66&�6(   $ 29Q�68   $ 29Q�6F   5     5     5     5     5  	   . �� Triggers. 5     P� 5  
   / P� Property/ �@d�	IsChecked0 P� Value$
0 TrueY�65   . �5     �� 1 �� 
TargetName$1 OffLight��6   2 �� Property2 � y�3 �� Value$3 Hidden=�6@   �� 5     $1 OnLight��6   2 � y�$3 Visible=�6?   5     P� 5  
   / � ��0 . . �5     �� $1 MainGrid��6   2 � z�3 5      T� 5!     4 T� X$4 1Q�6#   $) 1Q�6*   5#     5$     5&     5(     