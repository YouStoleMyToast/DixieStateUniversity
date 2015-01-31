using System.Collections.ObjectModel;
using System.ComponentModel;
using System; 

/// <summary>Summary description for Cell</summary>
namespace WpfSudoku
{
    public class Cell : INotifyPropertyChanged
    {
        public Cell(int maxval)
        {
            possibleValuesValue = new ObservableCollection<int?>();
            possibleValuesValue.Add(null);
            for (int i = 1; i <= maxval; i++)
            {
                possibleValuesValue.Add(i);
            }
        }
        bool readOnlyValue = false;
        public bool ReadOnly
        {
            get
            {
                return readOnlyValue;
            }
            set
            {
                if (readOnlyValue != value)
                {
                    readOnlyValue = value;
                    if (PropertyChanged != null) { PropertyChanged(this, new PropertyChangedEventArgs("ReadOnly")); }
                }
            }
        }
        int? valueValue = null;
        public int? Value
        {
            get
            {
                return valueValue;
            }
            set
            {
                if (valueValue != value)
                {
                    valueValue = value;
                    if (PropertyChanged != null) { PropertyChanged(this, new PropertyChangedEventArgs("Value")); }
                }
            }
        }
        ObservableCollection<int?> possibleValuesValue;
        public ObservableCollection<int?> PossibleValues
        {
            get
            {
                return possibleValuesValue;
            }
        }
        bool isValidValue = true;
        public bool IsValid
        {
            get
            {
                return isValidValue;
            }
            set
            {
                if (isValidValue != value)
                {
                    isValidValue = value;
                    if (PropertyChanged != null) { PropertyChanged(this, new PropertyChangedEventArgs("IsValid")); }
                }
            }
        }
        #region INotifyPropertyChanged Members
        public event PropertyChangedEventHandler PropertyChanged;
        #endregion
    }
}