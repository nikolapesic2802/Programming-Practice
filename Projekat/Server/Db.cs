﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;
namespace Server
{
    class Db
    {
        public static SqlConnection sqlConnection;
        public static DataSet dataSet;
    }
}
