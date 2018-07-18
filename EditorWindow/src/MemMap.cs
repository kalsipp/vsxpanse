using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Runtime.InteropServices;

namespace EditorWindow.src
{
    class MemMap
    {
        readonly long length = 1024; // 512 megabytes 
        string filepath;
        public MemMap()
        {
            var systemPath = System.Environment.
                             GetFolderPath(
                                 Environment.SpecialFolder.CommonApplicationData
                             );
            filepath = Path.Combine(systemPath, @"vsxpanse\item.data");
            Console.WriteLine("My path: " + filepath);
        }
        public void OpenMemMap()
        {
            if (!File.Exists(filepath))
            {
                (new FileInfo(filepath)).Directory.Create();
                using (File.Open(filepath, FileMode.CreateNew)) { }
            }
            MemoryMappedFileSecurity CustomSecurity = new MemoryMappedFileSecurity();
            CustomSecurity.AddAccessRule(new System.Security.AccessControl.AccessRule<MemoryMappedFileRights>
            ("everyone", MemoryMappedFileRights.FullControl, System.Security.AccessControl.AccessControlType.Allow));

            using (var file = File.Open(filepath, FileMode.Open))
            {
                using (var mmf = MemoryMappedFile.CreateFromFile(
                    file,
                    "myMapName",
                    length,
                    MemoryMappedFileAccess.ReadWrite,
                    CustomSecurity,
                    HandleInheritability.Inheritable,
                    false))
                {
                    // Create a random access view, from the 256th megabyte (the offset) 
                    // to the 768th megabyte (the offset plus length). 
                    using (var accessor = mmf.CreateViewAccessor(10, 42))
                    {

                        // Make changes to the view. 
                        accessor.Read(0, out int val);
                        val += 2;
                        Console.WriteLine(val);
                        accessor.Write(0, ref val);
                        
                    }
                }
            }
        }

    }
}


