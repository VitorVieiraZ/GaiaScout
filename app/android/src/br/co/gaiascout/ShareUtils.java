package br.co.gaiascout;

import android.content.Intent;
import android.net.Uri;
import android.app.Activity;
import androidx.core.content.FileProvider;
import java.io.File;

public class ShareUtils {
    // Share a file using an Intent
    public static void shareFile(Activity activity, String filePath) {
        File file = new File(filePath);
        Uri fileUri = FileProvider.getUriForFile(activity, "com.yourcompany.fieldwork.fileprovider", file);

        Intent shareIntent = new Intent(Intent.ACTION_SEND);
        shareIntent.setType("application/octet-stream");
        shareIntent.putExtra(Intent.EXTRA_STREAM, fileUri);
        shareIntent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);

        activity.startActivity(Intent.createChooser(shareIntent, "Share File"));
    }
}