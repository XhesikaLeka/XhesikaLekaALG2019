package webCrawler;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StringReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.xml.sax.InputSource;

public class WebCrawler {
	private static HttpURLConnection conn;
	private static ArrayList<String> links;
	private int Level;

	public WebCrawler() {
		WebCrawler.setLinks(new ArrayList<String>());
	}
	
	public static ArrayList<String> getLinks() {
		return links;
	}

	public static void setLinks(ArrayList<String> links) {
		WebCrawler.links = links;
	}

	public static String getText(String url) throws IOException {
	    HttpURLConnection connection = (HttpURLConnection) new URL(url).openConnection();

	    int responseCode = conn.getResponseCode();

    	System.out.println(responseCode);
	    InputStream inputStream;
	    if (200 <= responseCode && responseCode <= 299) {
	        inputStream = connection.getInputStream();
	    } else {
	        inputStream = connection.getErrorStream();
	    }

	    BufferedReader in = new BufferedReader(
	        new InputStreamReader(
	            inputStream));

	    StringBuilder response = new StringBuilder();
	    String currentLine;

	    while ((currentLine = in.readLine()) != null) 
	        response.append(currentLine);

	    in.close();

	    return response.toString();
	}
	
    private static Document convertStringToXMLDocument(String xmlString)
    {
        DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = null;
        try
        {
            builder = factory.newDocumentBuilder();
             
            Document doc = builder.parse(new InputSource(new StringReader(xmlString)));
            return doc;
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        return null;
    }
    
    public void getLink(String Url) {
    	if(Level == 4) {
    		return;
    	}
    	System.out.println("rec: "+Level);
    	String xmlStr = null;
		try {
			xmlStr = getText( Url);
		} catch (IOException e) {
			e.printStackTrace();
		}

		Document doc = convertStringToXMLDocument( xmlStr );
		NodeList nodes = doc.getElementsByTagName("a");
		for(int i=0;i<nodes.getLength();i++)
		{
			getLinks().add((String) ((DocumentBuilderFactory) nodes.item(i)).getAttribute("href"));
			getLink(getLinks().get(i));
		}
		Level++;
    }
	public static void main(String[] args) {
		WebCrawler wc = new WebCrawler();
		System.out.println("main ");
		wc.getLink("http://www.fshn.edu.al/");
		System.out.println(getLinks());
	}


}
