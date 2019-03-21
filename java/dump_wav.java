//
// @(#)dump_wav.java	2019/01/17
//
// Dump .wav(8bit mono) files to C Header files
//

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.UnsupportedAudioFileException;

/**
 * dump_wav
 */
public class dump_wav {
	static final String CRLF = "\r\n";

	static final String rootHeader = String.join(CRLF,
		"//",
		"// https://www.soundboard.com/sb/r2d2_r2_d2_sounds",
		"//",
		"",
		"#define SAMPLE_RATE "
	);

	static final String header = String.join(CRLF,
		"#include <M5Stack.h>",
		"",
		"const uint8_t " 
	);
	
	final int SAMPLE_RATE = 8000;
	
	dump_wav() throws UnsupportedAudioFileException, IOException {
		String srcFolder = "C:/Users/xxxx/Music/R2D2/8bit";
		String destFolder ="C:/Users/xxxx/Dev/IoT/m5stack/projects/M5Bala/src/sounds/";
		String prefix = "R2D2";
		
		dumpWaveFiles(srcFolder, destFolder, prefix);
	}
	
	boolean dumpWaveFile(File file, String destFolder, int sampleRate, boolean isTrim, ArrayList<String> waveNames) throws UnsupportedAudioFileException, IOException {
		String fileName = file.getName();
		System.out.println(fileName);
		String waveName = fileName.substring(0, fileName.lastIndexOf("."));
		waveNames.add(waveName);

		AudioInputStream ais = AudioSystem.getAudioInputStream(file);
		AudioFormat af = ais.getFormat();
		if (af.getChannels() != 1 || af.getFrameSize() != 1) {
			System.err.println("Wave file format error, must be 8bit mono");
			ais.close();
			return false;
		}
		int sampleRate1 = (int)Math.floor(af.getSampleRate());
		if (sampleRate != 0 && sampleRate1 != sampleRate) {
			System.out.println("Warning: sample rate do not match (" + Integer.toString(sampleRate1) + ")");
		}
		
		int frameLength = (int)ais.getFrameLength();
		byte[] buffer = new byte[frameLength]; // 8bit mono
		ais.read(buffer);
		ais.close();
		
		BufferedWriter bw = new BufferedWriter(new FileWriter(new File(destFolder + waveName + ".h")));
		bw.write(header);
		bw.write(makeFuncName(waveName) + "[] PROGMEM = {");

		int start = 0;
		int end = buffer.length;
		if (isTrim) {
			while(start < end) {
				int b = buffer[start];
				if (b != -128 && b != 127) break;
				start++;
			}
			while (end > start) {
				int b = buffer[end - 1];
				if (b != -128 && b != 127) break;
				end--;
			}
		}
		int lineBytes = 32;
		for (int i = start; i < end; i++) {
			if ((i % lineBytes) == 0) {
				bw.write(CRLF + "\t");
			}
			bw.write(String.format("%3d,", Byte.toUnsignedInt(buffer[i])));
		}
		bw.write(CRLF + "};" + CRLF);
		bw.close();
		return true;
	}
	
	void dumpWaveFiles(String srcFolder, String destFolder, String prefix) throws UnsupportedAudioFileException, IOException {
		ArrayList<String> waveNames = new ArrayList<String>();
		
		File[] files = new File(srcFolder).listFiles();
		Arrays.sort(files);
		for (File file : files) {
			if (!file.getName().toLowerCase().endsWith(".wav")) continue;
			dumpWaveFile(file, destFolder, SAMPLE_RATE, true, waveNames);
		}
		
		BufferedWriter bw = new BufferedWriter(new FileWriter(new File(destFolder + prefix + ".h")));
		bw.write(rootHeader + Integer.toString(SAMPLE_RATE) + CRLF + CRLF);
		for (String waveName : waveNames) {
			bw.write("#include \"" + waveName + ".h\"" + CRLF);
		}
		bw.write(CRLF);
		for (int i = 0; i < waveNames.size(); i++) {
			bw.write("#define " + makeFuncName(waveNames.get(i)).toUpperCase() + " " + i + CRLF);
		}
		bw.write(CRLF);
		bw.write("#define " + prefix + "_COUNT " + waveNames.size() + CRLF);
		bw.write(CRLF);
		bw.write("const uint8_t *waveDataArray[] = {" + CRLF);
		for (String waveName : waveNames) {
			bw.write("\t" + makeFuncName(waveName) + "," + CRLF);
		}
		bw.write("};" + CRLF + CRLF);
		bw.write("const uint16_t waveDataSizeArray[] = {" + CRLF);
		for (String waveName : waveNames) {
			bw.write("\tsizeof(" + makeFuncName(waveName) + ")," + CRLF);
		}
		bw.write("};" + CRLF);
	
		bw.close();
		System.out.println("done.");
	}

	String makeFuncName(String waveName) {
		return waveName.toLowerCase().replace("-", "_").replace(" ", "_");
	}
	
	public static void main(String[] args) throws UnsupportedAudioFileException, IOException {
		new dump_wav();
	}
}
