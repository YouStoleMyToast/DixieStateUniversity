   M S B A M L   `   `   `  ����   	WpfSudoku    WpfSudoku.SudokuBoard   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     @d2http://schemas.microsoft.com/expression/blend/2008     $��Stretch=�$��Stretch=�$��Stretch=�$��Stretch=�   ControlGradient#��[  ����   �� RelativeSource  �� *Self+ �� Path$ ActualHeight� � 	Resources   CellTemplate ��Name � ContextMenu �� 
TargetType �� Property �� Value �� 
TargetType	 ��Name
 �� SelectedItem �� Mode � DataContext �� Triggers �� Value �� Binding �� 
TargetName  InnerGridRowTemplate A� Rows  InnerGridTemplate A� Columns  OuterRowTemplate��%l  &	       &	 r    7  &	 �    7  &	     7  �� .R��� $ Border��
���iii�$��1q����	#00112233._��� |�.  $��Center=�$��Center=�$
��Bold"�$��24(����� $ Value� �� ���� " m�.���  � �� �� " m�.R��� $	 Header��$��Header����. .@��� $��0q�$��35��$��0q�$��Stretch=�$��Stretch=�
 �� $ Value�$ TwoWay=� ��   �� *TemplatedParent+$ DataContext����� $ PossibleValues� �� $ False�� �� *	IsValid+.a��� $ Border�� � ��
 �  ���� $
 True�� �� *
ReadOnly+.a��� $ Border�� � ��
 ��  ��� $ Border�� Z�  �@�ContextMenu�� .R��� 8��  ���� ���� .R�A� $ 1���� .R��� 
���   �$��1q�._��� 8��  ���� $ GridRows����� .R�A� $ 1���� .R��� 8��  ���� ���� .R�A� $ 1��.���� -    ��Name$ MainList��#��[ ���� $ GridRows����� .R�A� $ 1��