   M S B A M L   `   `   `  ����J  FSudokuFX, Version=1.0.5388.30936, Culture=neutral, PublicKeyToken=null#clr-namespace:SudokuFXSudokuFX  5          SudokuFX.Window1   5   	   \ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      $clrclr-namespace:SudokuFX    5      -   5          � Title$  SudokuFX��5      $	��800��6   $	��600��6"    � 	Resources 5         TimerAnimation W� From	 W� To �� 
TargetName g� Duration �� TargetProperty �� From	 �� To	 g� RepeatBehavior��%�  &	        �� 5	      -   5        .��5
      W� $ 0X�6   $ 1X�6"   $ StopwatchControl��6*   $ 0:2:0D�6U   $ CurrentTime�6f   �� 5      $ 1X�6   $ 0X�6!   $ 	MinNumber��6*   $	 Tag�6M   $ 0:2:0D�6n   �� 5      $ 59X�6   $ 0X�6"   $	 Forever��6*   $ 	SecNumber��6C   $	 Tag�6f   $ 0:1:0D�6�   �� 5      $ 59X�6   $ 0X�6"   $	 Forever��6*   $ SubSecNumber��6C   $	 Tag�6i   $ 0:0:1D�6�   5      5      .��5      ]�   GradientPanel#��[ 6   .+�5      � $	��Top=�6   $��	10,0,0,25q�6!   z�5      T� 5   
   
 T� X$	
 800Q�6    � Triggers 5      :� 5   
    :� RoutedEvent$ Control.Loaded��6   [�5      �� 5      .��5      �� .��5      U�  g� 	BeginTime$ 0:0:0.25X�61   $ RenderTransform.X�6G    g� AccelerationRatio$
 0.25Q�6v   .\�5      ��  O� Value$	 800Q�6)    O� KeyTime$ 0:0:0��65   �� 5      $	 -30Q�6)   $ 0:0:0.3��65   �� 5      $ 20Q�6)   $ 0:0:0.5��64   �� 5      $ 0Q�6)   $ 0:0:0.6��63   5      5       5!      5#      .+�5%      �� -   5         ��Name$ 	TitleText��5%   *   ���	#00112233$	��Top=�6>   $
��Left=�6V   
�������$��36(�6�   $��SudokuFX��6�   5&   	   �� 5'      -   5         ��Name$ TitleReflect��5'   G   $	��Top=�6   $
��Left=�6+   ��6_   ��  �� ElementName$ 	TitleText�� �� Path$ ActualWidth���6�   �� $ 	TitleText��$ ActualHeight�z�5(   
   V� 5)      .~�5*      ��  �� ScaleY$ -1Q�6Y    �� CenterY 6   �� $ 	TitleText��$ ActualHeight�6Y   T� 5+       T� Y$	 -10Q�6!   5,       J� OpacityMask 5.   
   �� 5/       �� 
StartPoint$	 0,0&�6     �� EndPoint$	 0,1&�62   .��50      �  � Color$ 	#00112233��6    � Offset$	 0.3Q�6.   � 51      $ 	#a0112233��6   $ 1Q�6.   52      54   	   55      �� 56      -   5         ��Name$ DockLeft��56      $
��Left=�6$   .+�57      9� -   5         9�Name$ 	MyControl��57       9� 
IsExpanded . $��	Main Menu��68   .��58   
   �� .+�59      �� -   5        .��59   *   
New Game64   �� 5:      -   5        .��5:   +   	Load Game66   �� 5;      -	   5        .��5;   +   	Save Game66   �� 5<      -
   5        .��5<   '   Quit6-   5=      5>   	   9� 5?       . $��New Game Settings��6$   .��5@   
   ��  5A        BoardSizeTemplate  �� Orientation��%�   &	       �� 5B      .R�5C      �� $  
Horizontal=�6   $��LeftToRight=�65   .+�5D      �� ��6   �� �� 5E      $��x��6   �� 5F      ��6   �� 5G      5H      5I      .+�5J      �� 
���   �Generation Method:6=   �� 5K      $��10,5,5,5q�6   .+�5L      	� -   5        ! 	�Name$! FastGenRadio��5L   ,   " d� 	IsChecked$
" TrueY�6   .��6C   Fast But Incorrect6W   	� 5M      .��6   Using Solver6)   5N      �� 5O      
���   �Timer Dificulty:6;   �� 5P      $��10,5,5,5q�6   .+�5Q      	� -   5        $! NoTimerRadio��5Q      .��60   
No Timer6:   	� 5R      -   5        $! EasyTimerRadio��5R      $
" TrueY�62   .��6D   Easy6J   	� 5S      -   5        $! MediumTimerRadio��5S      .��64   Medium6<   	� 5T      -   5        $! HardTimerRadio��5T      .��62   Hard68   5U      �� 5V      
���   �Board Size:66   O Kmscorlib, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e0891&clr-namespace:System;assembly=mscorlibSystem 5W   )   �� 6   2s&clr-namespace:System;assembly=mscorlib    6)   -   5        # ��Name$# 	BoardSize��5W      #��[ 6Z   $ �� 
IsEditable$ .  % �� SelectedItem% 5X      ��5Y      9��6   .@�5[      ��9��6   ��5\      16��6   ��5]      25��6   ��5^      36��6   5_      5`      5a   	   5b      �� 5c      -   5        $ 	DockRight��5c      $��Right=�6_   ��6%   �� $ DockLeft��$ ActualWidth�.+�5d      9�  . $��Current Game��6$   .��5e   
   1&clr-namespace:System;assembly=mscorlibSystem 6   �� 6
   2s&clr-namespace:System;assembly=mscorlib    6   .+�5f      �� -   5        $ TimerControls��5f      .+�5g      �� $  
Horizontal=�6   $��LeftToRight=�63   .+�5h      �� -   5        $ 	MinNumber��5h      $��36(�6/   $
��Bold"�6>   ��6Q   �� & �� RelativeSource& �� *Self+$	 Tag�
' � Tag' 5i      ��5j      59��6    5l      �� 5m      $��36(�6   $
��Bold"�6)   $��:��6;   �� 5n      -   5        $ 	SecNumber��5n      $��36(�6/   $
��Bold"�6>   ��6P   �� & �� *Self+$	 Tag�' 5o      ��5p      59��6    5r      �� 5s      $��0,5,0,0q�6   $��Center=�6+   $��24(�6G   $
��Bold"�6U   $��:��6g   �� 5t      -   5        $ SubSecNumber��5t   F   $��0,5,0,0q�6   $��Center=�6+   $��24(�6]   ��6l   �� & �� *Self+$	 Tag�' 5u      ��5v      59��6    5x      5y         SudokuFX.Stopwatch  5z      -   5        (  Name$( StopwatchControl��5z   ]      SudokuFX.Stopwatch)   Checked$) ResumeTimer��6   *   	Unchecked$* 
PauseTimer��62   $��0,5,0,0q�6K   $��Stretch=�6x   5{      �� 5|      -   5        .��5|   (   	I Give Up63   5}      5~   	   5      �� 5�        ControlBorder#��[ 6   $��Bottom=�65   ._�5�      ��   ControlInterior#��[ 6   $	��100��6:   .@�5�   
   �� .��6   Placed 5 at (3,9)5�      �� 5�   
   .��6   Placed 1 at (2,1)5�      �� 5�   
   .��6   Placed 8 at (7,4)5�      �� 5�   
   .��6   Placed 5 at (3,9)5�      �� 5�   
   .��6   Placed 1 at (2,1)5�      �� 5�   
   .��6   Placed 8 at (7,4)5�      �� 5�   
   .��6   Placed 5 at (3,9)5�      �� 5�   
   .��6   Placed 1 at (2,1)5�      �� 5�   
   .��6   Placed 8 at (7,4)5�      5�   	   5�      � 5�      .+�5�      �� $��6q�6\   
���������6   �� & �� *Self+$ ActualHeight�+ J� BitmapEffect+ 5�   
   F� 5�      , F� Opacity$	, 0.5Q�6#   5�   	      SudokuFX.SudokuBoard  5�      -   5        -  Name$- Board��5�      $��Stretch=�6(   $��Stretch=�6F   $��5q�6d   5�      5�      5�      