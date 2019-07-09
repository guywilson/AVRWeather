package com.guy.siteupload;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Properties;

import org.apache.commons.net.ftp.FTPClient;
import org.apache.commons.net.ftp.FTPReply;

public class siteUpload
{
	/**
	 * @param args
	 */
	public static void main(String[] args)
	{
		System.out.println("Started!");
			
		try {
			Properties prop = new Properties();

			try {
				InputStream propertiesIS = siteUpload.class.getClassLoader().getResourceAsStream("site.properties");
				prop.load(propertiesIS);
				propertiesIS.close();
			}
			catch(Exception e) {
				System.out.println("Failed to open properties file");
				throw e;
			}
			
			/*
			 * Properties...
			 */
			String portStr = prop.getProperty("ftp.port");
			int port = Integer.parseInt(portStr);
			String host = prop.getProperty("ftp.host");
			String username = prop.getProperty("ftp.username");
			String password = prop.getProperty("ftp.password");
			String wd = prop.getProperty("ftp.wd");
			String remoteFile = prop.getProperty("ftp.filename");
			String localFile = prop.getProperty("local.filename");

			InputStream is = null;
			
			System.out.println("Opening www.ipchicken.com");

			try {
				URL ipChicken = new URL("https://www.ipchicken.com/");
				is = ipChicken.openStream();
			}
			catch (Exception e) {
				System.out.println("Failed to get connection to www.ipchicken.com: " + e.getMessage());
				throw e;
			}
			
			if (is == null) {
				throw new Exception("Failed to open stream to www.ipchicken.com");
			}

			BufferedReader reader = new BufferedReader(new InputStreamReader(is));

            int c = 0;

            StringBuffer chickenBuffer = new StringBuffer();

            while (c != -1) {
                c = reader.read();
                chickenBuffer.append((char)(c & 0xFF));
            }

			reader.close();

			String ipAddr = "";

			int i = 0;
			int j = 0;

			/*
			** Find the public ip address...
			*/
			for (i = 0;i < chickenBuffer.length();i++) {
				if (Character.isDigit(chickenBuffer.charAt(i))) {
					int numDots = 0;

					for (j = 0;j < 15;j++) {
						if (chickenBuffer.charAt(j + i) == '.') {
							numDots++;
						}
						else if (chickenBuffer.charAt(j + i) == '<') {
							break;
						}
					}

					if (numDots == 3) {
						/*
						** Found an ip address...
						*/
						ipAddr = chickenBuffer.substring(i, j + i);
						break;
					}
				}
			}
			
			System.out.println("Found IP address : " + ipAddr);

            SimpleDateFormat df = new SimpleDateFormat("dd-MM-yyyy HH:mm:ss");
            String now = df.format(new Date());
			
			/*
			** Read the html template file...
			*/
			File inputFile = new File(localFile + ".template");
			FileInputStream fs = new FileInputStream(inputFile);
			byte[] weatherBuffer = fs.readAllBytes();

			fs.close();

			/*
			** Replace tokens in the template file...
			*/
			String weatherStr = new String(weatherBuffer);

			weatherStr = weatherStr.replaceAll("<TIME>", now);
			weatherStr = weatherStr.replaceAll("<SITE>", "http://" + ipAddr + ":4080");
			
			try {
				/*
				 * FTP the file to the web server... 
				 */
				int ftpResponseCode = 0;
				boolean success = true;
				
				System.out.println("FTP Upload");

				FTPClient ftp = new FTPClient();
				
				ftp.connect(host, port);
				ftpResponseCode = ftp.getReplyCode();
				
				if (!FTPReply.isPositiveCompletion(ftpResponseCode)) {
					throw new Exception("Failed to connect to host [" + ftpResponseCode + "].");
				}
				
				success = ftp.login(username, password);
				if (!success) {
					ftp.disconnect();
					throw new Exception("Failed to login to host.");
				}
				
				success = ftp.changeWorkingDirectory(wd);
				if (!success) {
					ftp.logout();
					ftp.disconnect();
					throw new Exception("Failed to change remote directory.");
				}
				
				ftp.enterLocalPassiveMode();
				
				ByteArrayInputStream in = new ByteArrayInputStream(weatherStr.getBytes());
				success = ftp.storeFile(remoteFile, in);
				if (!success) {
					ftp.logout();
					ftp.disconnect();
					throw new Exception("Failed to upload file.");
				}
				in.close();
				
				success = ftp.logout();
				if (!success) {
					ftp.disconnect();
					throw new Exception("Failed to logout.");
				}
				
				ftp.disconnect();
			}
			catch (Exception e) {
				System.out.println("FTP failed: " + e.getMessage());
				throw e;
			}
		}
		catch (Exception e) {
			System.out.println("Program failed: " + e.getMessage());
		}
	}
}
