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
using System.Windows.Threading;
using System.Diagnostics;
using System.Security;
using System.Security.Permissions;
using System.IO;
using System.Reflection;

//about classes
//fields: variables
//properties: getter and setter methods

//int? means it can be null
namespace WpfSudoku
{
    /// <summary>Interaction logic for MainWindow.xaml</summary>
    public partial class MainWindow : Window
    {
        ISudokuSolver Solver;
        long tms1 = DateTime.Now.Ticks;
        long tms2 = DateTime.Now.Ticks;
        public MainWindow()
        {
            InitializeComponent();
            tms1 = DateTime.Now.Ticks;
            DispatcherTimer timer = new DispatcherTimer();
            timer.Tick += new EventHandler(Timer);
            timer.Interval = new TimeSpan(0, 0, 1);
            timer.Start();
        }
        private void Timer(object sender, EventArgs e)
        {
            tms2 = DateTime.Now.Ticks;
            long dtms = tms2 - tms1;
            long msec = dtms / 10000000;
            long sec = msec % 60;
            long min = msec / 60;
            long hour = min / 60;
            string ss = sec.ToString("D2");
            string ms = min.ToString("D2");
            string hs = hour.ToString("D2");
            timeText.Content = hs + ":" + ms + ":" + ss;
            CommandManager.InvalidateRequerySuggested();
        }
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {

            Solver = LoadSolver("SampleSolver.dll");

            var workingArea = System.Windows.SystemParameters.WorkArea;
            this.Left = workingArea.Left;
            this.Top = workingArea.Top - this.Height;
        }
        private void newGame_Click(object sender, RoutedEventArgs e)
        {
            Board.GameBoard = new Board((int)BoardSize.SelectedItem);

            ComboBoxItem cbd = (ComboBoxItem)Difficulty.SelectedItem;
            string ComboBoxDifficulty = cbd.Content.ToString();
            if (String.Compare(ComboBoxDifficulty,"Hard")==0)
            {
                //Board.GameBoard.GenerateGame((int)BoardSize.SelectedItem * 2);
                Board.GameBoard.GenerateGameUsingSolver(Solver, (int)BoardSize.SelectedItem * 2);
            }
            else if (String.Compare(ComboBoxDifficulty, "Medium") == 0)
            {
                //Board.GameBoard.GenerateGame((int)BoardSize.SelectedItem * 3);
                Board.GameBoard.GenerateGameUsingSolver(Solver, (int)BoardSize.SelectedItem * 3);
            }
            else if (String.Compare(ComboBoxDifficulty, "Easy") == 0)
            {
                //Board.GameBoard.GenerateGame((int)BoardSize.SelectedItem * 4);
                Board.GameBoard.GenerateGameUsingSolver(Solver, (int)BoardSize.SelectedItem * 4);
            }
            tms1 = DateTime.Now.Ticks;
        }
        private void loadGame_Click(object sender, RoutedEventArgs e)
        {}
        private void saveGame_Click(object sender, RoutedEventArgs e)
        {}
        private void Quit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
        AppDomain pluginDomain = null;
        ISudokuSolver LoadSolver(string path)
        {
            if (pluginDomain == null)
            {
                AppDomainSetup ads = new AppDomainSetup();
                ads.ApplicationBase = AppDomain.CurrentDomain.BaseDirectory;
                PermissionSet ps = new PermissionSet(null);
                ps.AddPermission(new SecurityPermission(SecurityPermissionFlag.Execution));
                pluginDomain = AppDomain.CreateDomain("New AD", null, ads, ps);
            }
            FileStream stream = new FileStream(path, FileMode.Open, FileAccess.Read);
            byte[] assemblyData = new byte[stream.Length];
            stream.Read(assemblyData, 0, (int)stream.Length);
            Assembly asm = pluginDomain.Load(assemblyData);
            Type[] ts = asm.GetTypes();
            foreach (Type t in ts)
            {
                if (Array.IndexOf(t.GetInterfaces(), typeof(ISudokuSolver)) != -1)
                {
                    Type containter = typeof(SudokuSolver);
                    SudokuSolver ssc = pluginDomain.CreateInstanceAndUnwrap(containter.Assembly.FullName, containter.FullName) as SudokuSolver;
                    ssc.Init(t);
                    return ssc;
                }
            }
            return null;
        }
    }
}
