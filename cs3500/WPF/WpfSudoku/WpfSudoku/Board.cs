using System.Collections.ObjectModel;
using System.ComponentModel;
using System;

namespace WpfSudoku
{
    public class Board : INotifyPropertyChanged
    {
        ObservableCollection<ObservableCollection<InnerGrid>> Rows;
        public ObservableCollection<ObservableCollection<InnerGrid>> GridRows
        {
            get
            {
                return Rows;
            }
        }
        public int Size
        {
            get
            {
                return Rows.Count * Rows.Count;
            }
        }
        public Board(int totalsize)
        {
            int size = (int)Math.Sqrt(totalsize);
            Rows = new ObservableCollection<ObservableCollection<InnerGrid>>();
            for (int i = 0; i < size; i++)
            {
                ObservableCollection<InnerGrid> Col = new ObservableCollection<InnerGrid>();
                for (int j = 0; j < size; j++)
                {
                    InnerGrid g = new InnerGrid(size);
                    g.PropertyChanged += new PropertyChangedEventHandler(g_PropertyChanged);
                    Col.Add(g);
                }
                Rows.Add(Col);
            }
        }
        public int?[,] ToArray()
        {
            int?[,] t = new int?[this.Size, this.Size];
            for (int r = 0; r < this.Size; r++)
            {
                for (int c = 0; c < this.Size; c++)
                {
                    Cell cell = this[r, c];
                    if (cell.ReadOnly)
                    {
                        t[r, c] = -cell.Value;
                    }
                    else
                    {
                        t[r, c] = cell.Value;
                    }
                }
            }
            return t;
        }
        public void FromArray(int?[,] t)
        {
            if (t.GetLength(0) != t.GetLength(1) || t.GetLength(0) != this.Size)
            {
                throw new ArgumentOutOfRangeException("t", t, "Array is incorrect size");
            }
            for (int r = 0; r < this.Size; r++)
            {
                for (int c = 0; c < this.Size; c++)
                {
                    if (t[r, c] < 0)
                    {
                        this[r, c].Value = -t[r, c];
                        this[r, c].ReadOnly = true;
                    }
                    else
                    {
                        this[r, c].Value = t[r, c];
                    }
                }
            }
        }
        public void GenerateGameUsingSolver(ISudokuSolver s, int givens)
        {
            int size = Rows.Count * Rows.Count;
            if (givens < 0 || givens > size * size)
            {
                throw new ArgumentOutOfRangeException("givens", givens, "Invalid number of givens");
            }
            for (int r = 0; r < size; r++)
            {
                for (int c = 0; c < size; c++)
                {
                    Cell cell = this[r, c];
                    cell.ReadOnly = false;
                    cell.Value = null;
                }
            }
            Random rnd = new Random();
            int row = rnd.Next(size);
            int col = rnd.Next(size);
            this[row, col].Value = rnd.Next(size) + 1;
            int?[,] a = this.ToArray();
            s.Solve(ref a);
            this.FromArray(a);
            for (int i = 0; i < (size * size) - givens; i++)
            {
                for (; ; )
                {
                    int r = rnd.Next(size);
                    int c = rnd.Next(size);

                    Cell cell = this[r, c];
                    if (!cell.Value.HasValue) continue;
                    cell.Value = null;
                    cell.ReadOnly = false;
                    break;
                }
            }
            for (int r = 0; r < size; r++)
            {
                for (int c = 0; c < size; c++)
                {
                    Cell cell = this[r, c];
                    if (cell.Value.HasValue) cell.ReadOnly = true;
                }
            }
        }
        public void GenerateGame(int givens)
        {
            int size = Rows.Count * Rows.Count;
            if (givens < 0 || givens > size * size)
            {
                throw new ArgumentOutOfRangeException("givens", givens, "Invalid number of givens");
            }
            for (int r = 0; r < size; r++)
            {
                for (int c = 0; c < size; c++)
                {
                    Cell cell = this[r, c];
                    cell.ReadOnly = false;
                    cell.Value = null;
                }
            }
            Random rand = new Random();
            for (int i = 0; i < givens; i++)
            {
                bool givenFound;
                do
                {
                    givenFound = false;
                    Cell cell = null;
                    do
                    {
                        int row = rand.Next(size);
                        int col = rand.Next(size);
                        cell = this[row, col];
                    }
                    while (cell.Value != null);
                    int baseVal = rand.Next(size) + 1;
                    for (int v = 0; v < size; v++)
                    {
                        cell.Value = baseVal;
                        if (this.IsValid)
                        {
                            cell.ReadOnly = true;
                            givenFound = true;
                            break;
                        }
                        baseVal++;
                        if (baseVal > size) { baseVal = 1; }
                    }
                    if (!givenFound) { cell.Value = null; }
                }
                while (!givenFound);
            }
        }
        void g_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "IsValid")
            {
                bool valid = true;
                int totalsize = Rows.Count * Rows.Count;
                for (int i = 0; i < totalsize; i++)
                {
                    bool rowValid = CheckRowIsValid(i);
                    bool[] colValid = new bool[totalsize];
                    for (int j = 0; j < totalsize; j++)
                    {
                        colValid[j] = CheckColumnIsValid(j);
                    }
                    for (int j = 0; j < totalsize; j++)
                    {
                        bool innerGridValid = Rows[i / Rows.Count][j / Rows.Count].IsValid;
                        if (!colValid[j] || !rowValid || !innerGridValid) valid = false;
                        this[i, j].IsValid = colValid[j] & rowValid & innerGridValid;
                    }
                }
                isValidValue = valid;
                if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs("IsValid"));
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
        private bool CheckRowIsValid(int row)
        {
            int width = Rows.Count * Rows.Count;   
            bool[] used = new bool[width];
            for (int i = 0; i < width; i++)
            {
                Cell c = this[row, i];
                if (c.Value.HasValue)
                {
                    if (used[c.Value.Value-1])
                    {
                        return false;
                    }
                    else
                    {
                        used[c.Value.Value-1] = true; 
                    }
                }
            }
            return true;
        }
        private bool CheckColumnIsValid(int col)
        {
            int height = Rows.Count * Rows.Count;
            bool[] used = new bool[height];
            for (int i = 0; i < height; i++)
            {
                Cell c = this[i, col];
                if (c.Value.HasValue)
                {
                    if (used[c.Value.Value-1])
                    {
                        return false;
                    }
                    else
                    {
                        used[c.Value.Value-1] = true;
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
                int totalsize = Rows.Count * Rows.Count;
                if (row < 0 || row >= totalsize) throw new ArgumentOutOfRangeException("row", row, "Invalid Row Index");
                if (col < 0 || col >= totalsize) throw new ArgumentOutOfRangeException("col", col, "Invalid Column Index");
                return Rows[row / Rows.Count][col / Rows.Count][row % Rows.Count, col % Rows.Count];
            }
        }
    }
}

