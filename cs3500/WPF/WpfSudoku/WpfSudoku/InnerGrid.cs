using System.Collections.ObjectModel;
using System.ComponentModel;
using System; 
//innergrid is a 3x3 grid

namespace WpfSudoku
{
    public class InnerGrid : INotifyPropertyChanged
    {
        ObservableCollection<ObservableCollection<Cell>> Rows;
        public ObservableCollection<ObservableCollection<Cell>> GridRows
        {
            get
            {
                return Rows;
            }
        }
        public InnerGrid(int size)
        {
            Rows = new ObservableCollection<ObservableCollection<Cell>>();
            for (int i = 0; i < size; i++)
            {
                ObservableCollection<Cell> Col = new ObservableCollection<Cell>();
                for (int j = 0; j < size; j++)
                {
                    Cell c = new Cell(size*size); //after changing cell
                    c.PropertyChanged += new PropertyChangedEventHandler(c_PropertyChanged);
                    Col.Add(c);
                }
                Rows.Add(Col);
            }
        }
        void c_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "Value")
            {
                bool valid = CheckIsValid();
                foreach (ObservableCollection<Cell> r in Rows)
                {
                    foreach (Cell c in r)
                    {
                        c.IsValid = valid;
                    }
                }
                isValidValue = valid;
                if (PropertyChanged != null) { PropertyChanged(this, new PropertyChangedEventArgs("IsValid")); }
            }
        }
        bool isValidValue = true;
        public bool IsValid
        {
            get
            {
                return isValidValue;
            }
        }
        private bool CheckIsValid()
        {
            bool[] used = new bool[Rows.Count * Rows.Count];      
            foreach (ObservableCollection<Cell> r in Rows)
            {
                foreach (Cell c in r)
                {
                    if (c.Value.HasValue)
                    {
                        if (used[c.Value.Value-1])
                        {
                            return false; //this is a duplicate
                        }
                        else
                        {
                            used[c.Value.Value-1] = true; 
                        }
                    }
                 }
            }
            return true;
        }
        #region INotifyPropertyChanged Members
        public event PropertyChangedEventHandler PropertyChanged;
        #endregion
        public Cell this[int row, int col]
        {
            get
            {
                if (row < 0 || row >= Rows.Count) throw new ArgumentOutOfRangeException("row", row, "Invalid Row Index");
                if (col < 0 || col >= Rows.Count) throw new ArgumentOutOfRangeException("col", col, "Invalid Column Index");
                return Rows[row][col];
            }
        }
    }
}