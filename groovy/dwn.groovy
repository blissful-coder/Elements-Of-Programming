import java.nio.file.Files
import java.nio.file.Paths
import java.net.URL // Set the URL of the file you want to download
def fileUrl = "https://go.dev/dl/go1.17.2.linux-amd64.tar.gz"// Set the folder where you want to save the downloaded file
def folderPath = "."// Extract the file name from the URL
def fileName = fileUrl.substring(fileUrl.lastIndexOf("/") + 1)// Construct the full file path
def filePath = Paths.get(folderPath, fileName)// Download the file from the URL and save it to the folder
new URL(fileUrl).withInputStream { inputStream ->
Files.copy(inputStream, filePath)
}// Check if the file was downloaded successfully
if (Files.exists(filePath)) {
println "File downloaded successfully: ${filePath}"
} else {
println "Failed to download file."
}