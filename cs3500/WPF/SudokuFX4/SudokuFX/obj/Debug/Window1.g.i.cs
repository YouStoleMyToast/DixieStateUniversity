﻿#pragma checksum "..\..\Window1.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "35289AB0CD896696753F76A2281E09D7"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.18444
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using SudokuFX;
using System;
using System.Diagnostics;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Effects;
using System.Windows.Media.Imaging;
using System.Windows.Media.Media3D;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace SudokuFX {
    
    
    /// <summary>
    /// Window1
    /// </summary>
    public partial class Window1 : System.Windows.Window, System.Windows.Markup.IComponentConnector {
        
        
        #line 37 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock TitleText;
        
        #line default
        #line hidden
        
        
        #line 39 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Shapes.Rectangle TitleReflect;
        
        #line default
        #line hidden
        
        
        #line 54 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.StackPanel DockLeft;
        
        #line default
        #line hidden
        
        
        #line 55 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.Expander MyControl;
        
        #line default
        #line hidden
        
        
        #line 76 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.RadioButton FastGenRadio;
        
        #line default
        #line hidden
        
        
        #line 81 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.RadioButton NoTimerRadio;
        
        #line default
        #line hidden
        
        
        #line 82 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.RadioButton EasyTimerRadio;
        
        #line default
        #line hidden
        
        
        #line 83 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.RadioButton MediumTimerRadio;
        
        #line default
        #line hidden
        
        
        #line 84 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.RadioButton HardTimerRadio;
        
        #line default
        #line hidden
        
        
        #line 87 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.ComboBox BoardSize;
        
        #line default
        #line hidden
        
        
        #line 99 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.StackPanel DockRight;
        
        #line default
        #line hidden
        
        
        #line 102 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.StackPanel TimerControls;
        
        #line default
        #line hidden
        
        
        #line 104 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock MinNumber;
        
        #line default
        #line hidden
        
        
        #line 110 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock SecNumber;
        
        #line default
        #line hidden
        
        
        #line 116 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal System.Windows.Controls.TextBlock SubSecNumber;
        
        #line default
        #line hidden
        
        
        #line 122 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal SudokuFX.Stopwatch StopwatchControl;
        
        #line default
        #line hidden
        
        
        #line 165 "..\..\Window1.xaml"
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1823:AvoidUnusedPrivateFields")]
        internal SudokuFX.SudokuBoard Board;
        
        #line default
        #line hidden
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Uri resourceLocater = new System.Uri("/SudokuFX;component/window1.xaml", System.UriKind.Relative);
            
            #line 1 "..\..\Window1.xaml"
            System.Windows.Application.LoadComponent(this, resourceLocater);
            
            #line default
            #line hidden
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1811:AvoidUncalledPrivateCode")]
        internal System.Delegate _CreateDelegate(System.Type delegateType, string handler) {
            return System.Delegate.CreateDelegate(delegateType, this, handler);
        }
        
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        [System.CodeDom.Compiler.GeneratedCodeAttribute("PresentationBuildTasks", "4.0.0.0")]
        [System.ComponentModel.EditorBrowsableAttribute(System.ComponentModel.EditorBrowsableState.Never)]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Design", "CA1033:InterfaceMethodsShouldBeCallableByChildTypes")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Maintainability", "CA1502:AvoidExcessiveComplexity")]
        [System.Diagnostics.CodeAnalysis.SuppressMessageAttribute("Microsoft.Performance", "CA1800:DoNotCastUnnecessarily")]
        void System.Windows.Markup.IComponentConnector.Connect(int connectionId, object target) {
            switch (connectionId)
            {
            case 1:
            
            #line 5 "..\..\Window1.xaml"
            ((SudokuFX.Window1)(target)).Loaded += new System.Windows.RoutedEventHandler(this.WindowLoaded);
            
            #line default
            #line hidden
            return;
            case 2:
            
            #line 9 "..\..\Window1.xaml"
            ((System.Windows.Media.Animation.Storyboard)(target)).Completed += new System.EventHandler(this.TimerDone);
            
            #line default
            #line hidden
            return;
            case 3:
            this.TitleText = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 4:
            this.TitleReflect = ((System.Windows.Shapes.Rectangle)(target));
            return;
            case 5:
            this.DockLeft = ((System.Windows.Controls.StackPanel)(target));
            return;
            case 6:
            this.MyControl = ((System.Windows.Controls.Expander)(target));
            return;
            case 7:
            
            #line 57 "..\..\Window1.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.NewGameClicked);
            
            #line default
            #line hidden
            return;
            case 8:
            
            #line 58 "..\..\Window1.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.LoadGameClicked);
            
            #line default
            #line hidden
            return;
            case 9:
            
            #line 59 "..\..\Window1.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.SaveGameClicked);
            
            #line default
            #line hidden
            return;
            case 10:
            
            #line 60 "..\..\Window1.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.QuitClicked);
            
            #line default
            #line hidden
            return;
            case 11:
            this.FastGenRadio = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 12:
            this.NoTimerRadio = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 13:
            this.EasyTimerRadio = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 14:
            this.MediumTimerRadio = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 15:
            this.HardTimerRadio = ((System.Windows.Controls.RadioButton)(target));
            return;
            case 16:
            this.BoardSize = ((System.Windows.Controls.ComboBox)(target));
            return;
            case 17:
            this.DockRight = ((System.Windows.Controls.StackPanel)(target));
            return;
            case 18:
            this.TimerControls = ((System.Windows.Controls.StackPanel)(target));
            return;
            case 19:
            this.MinNumber = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 20:
            this.SecNumber = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 21:
            this.SubSecNumber = ((System.Windows.Controls.TextBlock)(target));
            return;
            case 22:
            this.StopwatchControl = ((SudokuFX.Stopwatch)(target));
            return;
            case 23:
            
            #line 124 "..\..\Window1.xaml"
            ((System.Windows.Controls.Button)(target)).Click += new System.Windows.RoutedEventHandler(this.SolveClicked);
            
            #line default
            #line hidden
            return;
            case 24:
            this.Board = ((SudokuFX.SudokuBoard)(target));
            return;
            }
            this._contentLoaded = true;
        }
    }
}

