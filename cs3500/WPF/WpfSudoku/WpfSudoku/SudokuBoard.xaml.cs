using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace WpfSudoku
{
    ///<summary>Interaction logic for SudokuBoard.xaml </summary>
    public partial class SudokuBoard : UserControl
    {
        public Board GameBoard
        {
            get
            {
                return MainList.DataContext as Board;
            }
            set
            {
                MainList.DataContext = value;
            }
        }
        public SudokuBoard()
        {
            InitializeComponent();
            //this.IsEnabled = false;
            GameBoard = new Board(9);
        }
    }
}